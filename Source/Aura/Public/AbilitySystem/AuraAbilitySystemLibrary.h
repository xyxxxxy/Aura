
#pragma once

#include "CoreMinimal.h"
#include "AuraAbilityTypes.h"
#include "GameplayEffectTypes.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Data/CharacterClassInfo.h"
#include "AuraAbilitySystemLibrary.generated.h"

class UAbilitySystemComponent;
class UAttributeMenuWidgetController;
class UOverlayWidgetController;

UCLASS()
class AURA_API UAuraAbilitySystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure,Category = "AuraAbilitySystemLibrary|WidgetController")
	static UOverlayWidgetController* GetOverlayWidgetController(const UObject* WorldContextUObject);

	UFUNCTION(BlueprintPure,Category = "AuraAbilitySystemLibrary|WidgetController")
	static UAttributeMenuWidgetController* GetAttributeMenuWidgetController(const UObject* WorldContextUObject);

	UFUNCTION(BlueprintCallable,Category = "AuraAbilitySystemLibrary|CharacterClassDefaults")
	static void InitializeDefaultAttributes(const UObject* WorldContextUObject,ECharacterClass CharacterClass,float Level,UAbilitySystemComponent* ASC);

	UFUNCTION(BlueprintCallable,Category = "AuraAbilitySystemLibrary|CharacterClassDefaults")
	static void GiveStartupAbilities(const UObject* WorldContextUObject,UAbilitySystemComponent* ASC,ECharacterClass CharacterClass);
	
	UFUNCTION(BlueprintCallable,Category = "AuraAbilitySystemLibrary|CharacterClassDefaults")
	static UCharacterClassInfo* GetCharacterClassInfo(const UObject* WorldContextUObject);

	UFUNCTION(BlueprintCallable,Category = "AuraAbilitySystemLibrary|GameplayEffects")
	static void SetDamageTypes(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle,const FDamageTypes& InDamageTypes);

	UFUNCTION(BlueprintPure,Category = "AuraAbilitySystemLibrary|GameplayEffects")
	static FDamageTypes GetDamageTypes(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle);

	UFUNCTION(BlueprintCallable,Category = "AuraAbilitySystemLibrary|GameplayMechanics")
	static void GetLivePlayersWithRadius(const UObject* WorldContextObject,TArray<AActor*>& OutOverlappingActors,const TArray<AActor*> ActorsToIgnore,float Radius,const FVector& SphereOrigin);

	UFUNCTION(BlueprintPure,Category = "AuraAbilitySystemLibrary|GameplayMechanics")
	static bool IsNotFriend(const AActor* FirstActor,const AActor* SecondActor);

};
