
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerControllerBase.generated.h"

class USplineComponent;
class UAuraAbilitySystemComponent;
class UAuraInputConfig;
struct FGameplayTag;
struct FInputActionValue;
class UInputMappingContext;
class UInputAction;
class IEnemyInterface;

UCLASS()
class AURA_API AAuraPlayerControllerBase : public APlayerController
{
	GENERATED_BODY()
	
public:
	AAuraPlayerControllerBase();
	virtual void PlayerTick(float DeltaTime) override;
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

private:
	UPROPERTY(EditAnywhere,Category = "Input")
	TObjectPtr<UInputMappingContext> AuraContext;

	UPROPERTY(EditAnywhere,Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere,Category = "Input")
	TObjectPtr<UInputAction> ShiftAction;

	void ShiftPressed(){bShiftKeyDown = true;}
	void ShiftReleased(){bShiftKeyDown = false;}
	bool bShiftKeyDown = false;

	void Move(const FInputActionValue& InputActionValue);

	void CursorTrace();
	FHitResult CursorHit;
	IEnemyInterface* LastActor{nullptr};
	IEnemyInterface* ThisActor{nullptr};
	
	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);

	UPROPERTY(EditDefaultsOnly,Category = "Input")
	TObjectPtr<UAuraInputConfig> InputConfig;

	UPROPERTY()
	TObjectPtr<UAuraAbilitySystemComponent> AuraAbilitySystemComponent;

	UAuraAbilitySystemComponent* GetASC();

	FVector CachedDestination = FVector::ZeroVector;
	float FollowTime = 0.f;
	float ShortPressThreshold = .5f;
	bool bAutoRunning = false;
	bool bTargeting = false;

	UPROPERTY(EditDefaultsOnly)
	float AutoRunAcceptanceRadius = 50.f;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> Spline;

	void AutoRun();
};
