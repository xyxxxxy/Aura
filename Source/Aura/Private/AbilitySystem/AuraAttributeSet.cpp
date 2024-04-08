
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Net/UnrealNetwork.h"

UAuraAttributeSet::UAuraAttributeSet()
{
}

void UAuraAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	//条件复制
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,HP,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,MaxHP,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,MP,COND_None,REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UAuraAttributeSet,MaxMP,COND_None,REPNOTIFY_Always);
}

void UAuraAttributeSet::OnRep_HP(const FGameplayAttributeData& OldHP) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,HP,OldHP);
}

void UAuraAttributeSet::OnRep_MaxHP(const FGameplayAttributeData& OldMaxHP) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,HP,OldMaxHP);
}

void UAuraAttributeSet::OnRep_MP(const FGameplayAttributeData& OldMP) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,HP,OldMP);
}

void UAuraAttributeSet::OnRep_MaxMP(const FGameplayAttributeData& OldMaxMP) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UAuraAttributeSet,HP,OldMaxMP);
}
