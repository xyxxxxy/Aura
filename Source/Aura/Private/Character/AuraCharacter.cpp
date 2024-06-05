
#include "Character/AuraCharacter.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystem/AuraAbilitySystemComponent.h"
#include "Player/AuraPlayerControllerBase.h"
#include "Player/AuraPlayerState.h"
#include "UI/HUD/AuraHUD.h"

AAuraCharacter::AAuraCharacter()
{
	Tags.Add(FName("Player"));
}

void AAuraCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitAbilityActorInfo();
	AddCharacterAbilities();
}

void AAuraCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();

	InitAbilityActorInfo();
}

int32 AAuraCharacter::GetPlayerLevel()
{
	const AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	return AuraPlayerState->GetPlayerLevel();
}

void AAuraCharacter::InitAbilityActorInfo()
{
	AAuraPlayerState* AuraPlayerState = GetPlayerState<AAuraPlayerState>();
	check(AuraPlayerState);
	AuraPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(AuraPlayerState,this);
	AbilitySystemComponent = AuraPlayerState->GetAbilitySystemComponent();
	Cast<UAuraAbilitySystemComponent>(AbilitySystemComponent)->AbilityActorInfoSet();

	AttributeSet = AuraPlayerState->GetAttributeSet();

	if(AAuraPlayerControllerBase* AuraPlayerControllerBase = Cast<AAuraPlayerControllerBase>(GetController()))
	{
		if(AAuraHUD* AuraHUD = Cast<AAuraHUD>(AuraPlayerControllerBase->GetHUD()))
		{
			AuraHUD->InitOverlay(AuraPlayerControllerBase,AuraPlayerState,AbilitySystemComponent,AttributeSet);
		}
	}
	InitializeDefaultAttributes();
}
