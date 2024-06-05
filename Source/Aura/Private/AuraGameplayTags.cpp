
#include "AuraGameplayTags.h"
#include "GameplayTagsManager.h"

FAuraGameplayTags FAuraGameplayTags::GameplayTags;

void FAuraGameplayTags::InitializeNativeGameplayTags()
{
	UGameplayTagsManager& Manager = UGameplayTagsManager::Get();
	GameplayTags.AddAllTags(Manager);

	
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Fire,GameplayTags.Attributes_Resistance_Fire);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Arcane,GameplayTags.Attributes_Resistance_Arcane);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Lightning,GameplayTags.Attributes_Resistance_Lightning);
	GameplayTags.DamageTypesToResistances.Add(GameplayTags.Damage_Physical,GameplayTags.Attributes_Resistance_Physical);


}

void FAuraGameplayTags::AddAllTags(UGameplayTagsManager& Manager)
{
	//Primary Attributes
	AddTag(Attributes_Primary_Strength,"Attributes.Primary.Strength","Increases physical damage");
	AddTag(Attributes_Primary_Intelligence,"Attributes.Primary.Intelligence","Increases magical damage");
	AddTag(Attributes_Primary_Resilience,"Attributes.Primary.Resilience","Increases armor and armor penetration");
	AddTag(Attributes_Primary_Vigor,"Attributes.Primary.Vigor","Increases health");

	//Secondary Attributes
	AddTag(Attributes_Secondary_Armor,"Attributes.Secondary.Armor","Reduce damage taken, improves Block Chance");
	AddTag(Attributes_Secondary_ArmorPenetration,"Attributes.Secondary.ArmorPenetration","Ignores Percentage of enemy Armor, increases Critical Hit Chance");
	AddTag(Attributes_Secondary_BlockChance,"Attributes.Secondary.BlockChance","Chance to cut incoming damage in half");
	AddTag(Attributes_Secondary_CriticalHitChance,"Attributes.Secondary.CriticalHitChance","Chance to double damage plus critical hit bonus");
	AddTag(Attributes_Secondary_CriticalHitDamage,"Attributes.Secondary.CriticalHitDamage","Bonus damage added when a critical hit is scored");
	AddTag(Attributes_Secondary_CriticalHitResistance,"Attributes.Secondary.CriticalHitResistance","Reduces Critical Hit Chance of Attacking enemies");
	AddTag(Attributes_Secondary_HealthRegeneration,"Attributes.Secondary.HealthRegeneration","Amount of Health regenerated every 1 second");
	AddTag(Attributes_Secondary_ManaRegeneration,"Attributes.Secondary.ManaRegeneration","Amount of Mana regenerated every 1 second");
	AddTag(Attributes_Secondary_MaxHealth,"Attributes.Secondary.MaxHealth","Maximum amount of Health obtainable");
	AddTag(Attributes_Secondary_MaxMana,"Attributes.Secondary.MaxMana","Maximum amount of Mana obtainable");

	//Input Tags
	AddTag(InputTag_LMB,"InputTag.LMB","Input Tag for Left Mouse Button");
	AddTag(InputTag_RMB,"InputTag.RMB","Input Tag for Right Mouse Button");
	AddTag(InputTag_1,"InputTag.1","Input Tag for 1 key");
	AddTag(InputTag_2,"InputTag.2","Input Tag for 2 key");
	AddTag(InputTag_3,"InputTag.3","Input Tag for 3 key");
	AddTag(InputTag_4,"InputTag.4","Input Tag for 4 key");

	//Damage Types
	AddTag(Damage,"Damage","Damage");
	AddTag(Damage_Fire,"Damage.Fire","Fire Damage type");
	AddTag(Damage_Lightning,"Damage.Lightning","Lightning Damage type");
	AddTag(Damage_Arcane,"Damage.Arcane","Arcane Damage type");
	AddTag(Damage_Physical,"Damage.Physical","Physical Damage type");

	//Resistances
	AddTag(Attributes_Resistance_Fire,"Damage.Resistance.Fire","Resistance to Fire damage");
	AddTag(Attributes_Resistance_Lightning,"Damage.Resistance.Lightning","Resistance to Lightning damage");
	AddTag(Attributes_Resistance_Arcane,"Damage.Resistance.Arcane","Resistance to Arcane damage");
	AddTag(Attributes_Resistance_Physical,"Damage.Resistance.Physical","Resistance to Physical damage");

	//Effects
	AddTag(Effects_HitReact,"Effects.HitReact","Tag granted when Hit Reacting");

	//Abilities
	AddTag(Abilities_Attack,"Abilities.Attack","Attack Ability Tag");
	AddTag(Abilities_Fire_FireBolt,"Abilities.Fire.FireBolt","FireBolt Ability Tag");

	//Montages
	AddTag(Montage_Attack_Weapon,"Montage.Attack.Weapon","Weapon");
	AddTag(Montage_Attack_LeftHand,"Montage.Attack.LeftHand","LeftHand");
	AddTag(Montage_Attack_RightHand,"Montage.Attack.RightHand","RightHand");
}

void FAuraGameplayTags::AddTag(FGameplayTag& OutTag, const ANSICHAR* TagName, const ANSICHAR* TagComment)
{
	OutTag = UGameplayTagsManager::Get().AddNativeGameplayTag(FName(TagName),FString(TEXT("(Native) ")) + FString(TagComment));
}
