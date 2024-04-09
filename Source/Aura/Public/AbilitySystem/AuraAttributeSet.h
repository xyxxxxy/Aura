
#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "AuraAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

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
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,HP)
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_MaxHP,Category = "Vital Attribute")
	FGameplayAttributeData MaxHP;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,MaxHP)
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_MP,Category = "Vital Attribute")
	FGameplayAttributeData MP;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,MP)
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing = OnRep_MaxMP,Category = "Vital Attribute")
	FGameplayAttributeData MaxMP;
	ATTRIBUTE_ACCESSORS(UAuraAttributeSet,MaxMP)

	UFUNCTION()
	void OnRep_HP(const FGameplayAttributeData& OldHP) const;
	
	UFUNCTION()
	void OnRep_MaxHP(const FGameplayAttributeData& OldMaxHP) const;
	
	UFUNCTION()
	void OnRep_MP(const FGameplayAttributeData& OldMP) const;
	
	UFUNCTION()
	void OnRep_MaxMP(const FGameplayAttributeData& OldMaxMP) const;
};
