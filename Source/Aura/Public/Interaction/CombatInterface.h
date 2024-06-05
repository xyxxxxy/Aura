
#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

USTRUCT(BlueprintType)
struct FTaggedMontage
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	UAnimMontage* Montage = nullptr;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly)
	FGameplayTag MontageTag;
};


UINTERFACE(MinimalAPI,BlueprintType)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

class AURA_API ICombatInterface
{
	GENERATED_BODY()

public:
	virtual int32 GetPlayerLevel();

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	FVector GetCombatSocketLocation(const FGameplayTag& MontageTag);

	UFUNCTION(BlueprintImplementableEvent,BlueprintCallable)
	void UpdateFacingTarget(const FVector& Target);

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	UAnimMontage* GetHitReactMontage();

	virtual void Die();

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	bool IsDead() const;

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	AActor* GetAvatar();

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	TArray<FTaggedMontage> GetAttackMontages();


};
