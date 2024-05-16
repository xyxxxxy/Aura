
#pragma once

#include "GameplayEffectTypes.h"
#include "AuraAbilityTypes.generated.h"

USTRUCT(BlueprintType)
struct FDamageTypes
{
	GENERATED_BODY()

	FDamageTypes(){bIsBlockingHit = false; bIsBlockingHit = false;}
	FDamageTypes(const FDamageTypes& InDamageTypes)
	{
		bIsBlockingHit = InDamageTypes.bIsBlockingHit;
		bIsCriticalHit = InDamageTypes.bIsCriticalHit;
	}
	FDamageTypes(bool bInIsBlockingHit,bool bInIsCriticalHit)
	{
		bIsBlockingHit = bInIsBlockingHit;
		bIsCriticalHit = bInIsCriticalHit;
	}

	bool IsBlockingHit() const {return  bIsBlockingHit;} 
	bool IsCriticalHit() const {return  bIsCriticalHit;} 
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bIsBlockingHit = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bIsCriticalHit = false;
};

USTRUCT(BlueprintType)
struct FAuraGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()

public:
	
	/** Returns the actual struct used for serialization, subclasses must override this! */
	virtual UScriptStruct* GetScriptStruct() const
	{
		return FGameplayEffectContext::StaticStruct();
	}
	/** Custom serialization, subclasses must override this */
	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess);
	
	void SetDamageTypes(const FDamageTypes& InDamageTypes)
	{
		DamageTypes.bIsBlockingHit = InDamageTypes.bIsBlockingHit;
		DamageTypes.bIsCriticalHit = InDamageTypes.bIsCriticalHit;
	}
	FDamageTypes& GetDamageTypes(){return DamageTypes;}

protected:

	UPROPERTY()
	FDamageTypes DamageTypes;
};

template<>
struct TStructOpsTypeTraits<FAuraGameplayEffectContext> : TStructOpsTypeTraitsBase2<FAuraGameplayEffectContext>
{
	enum
	{
		WithNetSerializer = true,
		WithCopy = true
	};
};