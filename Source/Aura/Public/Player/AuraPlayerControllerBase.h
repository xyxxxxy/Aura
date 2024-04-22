
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AuraPlayerControllerBase.generated.h"

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

	IEnemyInterface* LastActor{nullptr};
	IEnemyInterface* ThisActor{nullptr};
	
private:
	UPROPERTY(EditAnywhere,Category = "Input")
	TObjectPtr<UInputMappingContext> AuraContext;

	UPROPERTY(EditAnywhere,Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	void CursorTrace();

	void Move(const FInputActionValue& InputActionValue);
};
