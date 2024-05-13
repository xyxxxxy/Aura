
#pragma once

#include "CoreMinimal.h"
#include "Abilities/Tasks/AbilityTask.h"
#include "TargetDataUnderMouse.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FTargetDataSignature,const FGameplayAbilityTargetDataHandle&, DataHandle);
UCLASS()
class AURA_API UTargetDataUnderMouse : public UAbilityTask
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable,meta = (Displayname = "TargetDataUnderMouse",HidePin = "OwningAbility",DefaultToSelf = "OwningAbility",BlueprintInternalUseOnly = "true"))
	static UTargetDataUnderMouse* CreateTargetDataUnderMouse(UGameplayAbility* OwningAbility);

	UPROPERTY(BlueprintAssignable)
	FTargetDataSignature ValidData;

private:
	virtual void Activate() override;
	void SendMouseCursorData();
	void OnTargetDataReplicatedCallBack(const FGameplayAbilityTargetDataHandle& DataHandle,FGameplayTag ActivationTag);
};
