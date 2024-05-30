
#pragma once

#include "CoreMinimal.h"
#include "Character/AuraCharacterBase.h"
#include "AuraCharacter.generated.h"

UCLASS()
class AURA_API AAuraCharacter : public AAuraCharacterBase
{
	GENERATED_BODY()

public:

	AAuraCharacter();
	//server
	virtual void PossessedBy(AController* NewController) override;
	//client
	virtual void OnRep_PlayerState() override;

	virtual int32 GetPlayerLevel() override;

protected:
	virtual void InitAbilityActorInfo() override;
};
