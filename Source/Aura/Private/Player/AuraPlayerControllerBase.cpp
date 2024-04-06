// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/AuraPlayerControllerBase.h"

#include "../../../../../../../UE/UE_5.2/Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputComponent.h"
#include "../../../../../../../UE/UE_5.2/Engine/Plugins/EnhancedInput/Source/EnhancedInput/Public/EnhancedInputSubsystems.h"
#include "Interaction/EnemyInterface.h"

AAuraPlayerControllerBase::AAuraPlayerControllerBase()
{
	bReplicates = true;
}

void AAuraPlayerControllerBase::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	CursorTrace();
}

void AAuraPlayerControllerBase::BeginPlay()
{
	Super::BeginPlay();

	check(AuraContext);

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::
	GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	check(Subsystem);

	Subsystem->AddMappingContext(AuraContext,0);

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
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&AAuraPlayerControllerBase::Move);
}

void AAuraPlayerControllerBase::CursorTrace()
{
	FHitResult CursorHit;
	GetHitResultUnderCursor(ECC_Visibility,false,CursorHit);
	if(!CursorHit.GetActor())return;

	LastActor = ThisActor;
	ThisActor = Cast<IEnemyInterface>(CursorHit.GetActor());
	if(LastActor == nullptr)
	{
		if(ThisActor != nullptr)
		{
			//B
			ThisActor->HighLightActor();
		}
		else
		{
			//A
		}
	}
	else // LastActor is valid
	{
		if(ThisActor == nullptr)
		{
			//C
			LastActor->UnHighLightActor();
		}
		else
		{
			if(ThisActor == LastActor)
			{
				//E
			}
			else
			{
				LastActor->UnHighLightActor();
				ThisActor->HighLightActor();
			}
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
