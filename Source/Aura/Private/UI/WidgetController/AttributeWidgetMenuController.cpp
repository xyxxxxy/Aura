
#include "AbilitySystem/AuraAttributeSet.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "UI/WidgetController/AttributeMenuWidgetController.h"

void UAttributeMenuWidgetController::BindCallbacksToDependencies()
{
	const UAuraAttributeSet* AS = CastChecked<UAuraAttributeSet>(AttributeSet);
	for(auto& Pair : AS->TagsToAttributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda(
			[this,Pair,AS](const FOnAttributeChangeData& Data)
			{
				BroadcastAttributeInfo(Pair.Key,Pair.Value());
			}
			);		
	}
}

void UAttributeMenuWidgetController::BroadcastInitialValues()
{
	const UAuraAttributeSet* AS = Cast<UAuraAttributeSet>(AttributeSet);
	
	check(AttributeInfo);

	for (auto& Pair : AS->TagsToAttributes)
	{
		BroadcastAttributeInfo(Pair.Key,Pair.Value());
	}
}

void UAttributeMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag,
	const FGameplayAttribute& Attribute) const
{
	FAuraAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(AttributeTag);
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
}
