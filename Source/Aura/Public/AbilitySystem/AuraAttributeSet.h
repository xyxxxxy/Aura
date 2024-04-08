
#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AuraAttributeSet.generated.h"

UCLASS()
class AURA_API UAuraAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UAuraAttributeSet();
	//用于获取要复制到客户端的属性列表
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_HP,Category = "Vital Attribute")
	FGameplayAttributeData HP;
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_MaxHP,Category = "Vital Attribute")
	FGameplayAttributeData MaxHP;
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_MP,Category = "Vital Attribute")
	FGameplayAttributeData MP;
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_MaxMP,Category = "Vital Attribute")
	FGameplayAttributeData MaxMP;

	UFUNCTION()
	void OnRep_HP(const FGameplayAttributeData& OldHP) const;
	
	UFUNCTION()
	void OnRep_MaxHP(const FGameplayAttributeData& OldMaxHP) const;
	
	UFUNCTION()
	void OnRep_MP(const FGameplayAttributeData& OldMP) const;
	
	UFUNCTION()
	void OnRep_MaxMP(const FGameplayAttributeData& OldMaxMP) const;
};
