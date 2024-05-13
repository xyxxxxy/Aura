
#include "Player/AuraPlayerControllerBase.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AuraGameplayTags.h"
#include "EnhancedInputSubsystems.h"
#include "Interaction/EnemyInterface.h"
#include "GameplayTagContainer.h"
#include "NavigationPath.h"
#include "NavigationSystem.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Components/SplineComponent.h"
#include "Input/AuraInputComponent.h"

AAuraPlayerControllerBase::AAuraPlayerControllerBase()
{
	bReplicates = true;

	Spline = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
}

void AAuraPlayerControllerBase::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
	AutoRun();
}

void AAuraPlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();

	check(AuraContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::
	GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	
	if(Subsystem)
	{
		Subsystem->AddMappingContext(AuraContext,0);
	}
	
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Default;

	FInputModeGameAndUI InputModeData;
	InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	InputModeData.SetHideCursorDuringCapture(false);

	SetInputMode(InputModeData);
}

void AAuraPlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();
	UAuraInputComponent* AuraInputComponent = CastChecked<UAuraInputComponent>(InputComponent);
	AuraInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AAuraPlayerControllerBase::Move);
	AuraInputComponent->BindAction(ShiftAction,ETriggerEvent::Started,this,&AAuraPlayerControllerBase::ShiftPressed);
	AuraInputComponent->BindAction(ShiftAction,ETriggerEvent::Completed,this,&AAuraPlayerControllerBase::ShiftReleased);
	AuraInputComponent->BindAbilityActions(InputConfig,this,&ThisClass::AbilityInputTagPressed,&ThisClass::AbilityInputTagReleased,&ThisClass::AbilityInputTagHeld);
}

void AAuraPlayerControllerBase::CursorTrace()
{
	GetHitResultUnderCursor(ECC_Visibility,false,CursorHit);
	if(!CursorHit.GetActor())return;

	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());

	if(LastActor != ThisActor)
	{
		if(LastActor)
		{
			LastActor->UnHighLightActor();
		}
		if(ThisActor)
		{
			ThisActor->HighLightActor();
		}
	}
}

void AAuraPlayerControllerBase::Move(const FInputActionValue& InputActionValue)
{
	const FVector2D InputAxisVector = InputActionValue.Get<FVector2D>();
	const FRotator YawRotation(0.f,GetControlRotation().Yaw,0.f);

	const FVector ForwardDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDir = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	if(APawn* ControllerPawn = GetPawn())
	{
		ControllerPawn->AddMovementInput(ForwardDir,InputAxisVector.Y);
		ControllerPawn->AddMovementInput(RightDir,InputAxisVector.X);
	}
}

void AAuraPlayerControllerBase::AbilityInputTagPressed(FGameplayTag InputTag)
{
	if(InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		bTargeting = ThisActor ? true : false;
		bAutoRunning = false;
	}
}

void AAuraPlayerControllerBase::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if(!GetASC())return;
	
	if(!InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		GetASC()->AbilityInputTagReleased(InputTag);
		return;
	}
	if(GetASC())GetASC()->AbilityInputTagReleased(InputTag);
	if (!bTargeting && !bShiftKeyDown)
	{
		const APawn* ControllerPawn = GetPawn();
		if(FollowTime <= ShortPressThreshold && ControllerPawn)
		{
			UNavigationPath* NavPath = UNavigationSystemV1::FindPathToLocationSynchronously(
				this,ControllerPawn->GetActorLocation(),CachedDestination);
			if(!NavPath)return;
			Spline->ClearSplinePoints();
			for(FVector& PointLoc : NavPath->PathPoints)
			{
				Spline->AddSplinePoint(PointLoc,ESplineCoordinateSpace::World);
			}
			// Ignore NavPath Last Point，Prevents mouse clicks from being located outside the navigation Mesh
			CachedDestination = NavPath->PathPoints[NavPath->PathPoints.Num() - 1];
			bAutoRunning = true;
		}
		FollowTime = 0.f;
		bTargeting = false;
	}
}

void AAuraPlayerControllerBase::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if(!InputTag.MatchesTagExact(FAuraGameplayTags::Get().InputTag_LMB))
	{
		if(GetASC())
		{
			GetASC()->AbilityInputTagHeld(InputTag);
			return;
		}
	}
	if (bTargeting || bShiftKeyDown)
	{
		if(GetASC())
		{
			GetASC()->AbilityInputTagHeld(InputTag);
		}
	}
	else
	{
		FollowTime += GetWorld()->GetDeltaSeconds();
		
		if(CursorHit.bBlockingHit)
		{
			CachedDestination = CursorHit.ImpactPoint;
		}
		
		if(APawn* ControllerPawn = GetPawn())
		{
			const FVector WorldDirection = (CachedDestination - ControllerPawn->GetActorLocation()).GetSafeNormal();
			ControllerPawn->AddMovementInput(WorldDirection);
		}
	}
}

UAuraAbilitySystemComponent* AAuraPlayerControllerBase::GetASC()
{
	if(AuraAbilitySystemComponent == nullptr)
	{
		AuraAbilitySystemComponent = Cast<UAuraAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	return AuraAbilitySystemComponent;
}

void AAuraPlayerControllerBase::AutoRun()
{
	if(!bAutoRunning)return;
	if(APawn* ControllerPawn = GetPawn())
	{
		const FVector LocationOnSpline = Spline->FindLocationClosestToWorldLocation(ControllerPawn->GetActorLocation(),ESplineCoordinateSpace::World);
		const FVector Direction = Spline->FindDirectionClosestToWorldLocation(LocationOnSpline,ESplineCoordinateSpace::World);
		ControllerPawn->AddMovementInput(Direction);

		const float DistanceToDestination = (LocationOnSpline - CachedDestination).Length();
		if(DistanceToDestination <= AutoRunAcceptanceRadius)
		{
			bAutoRunning = false;
		}
	}
}
