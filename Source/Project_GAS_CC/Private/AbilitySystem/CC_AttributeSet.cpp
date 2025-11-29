// Copyrights to Mahdi94x based on Course Make exciting multiplayer and single player games with the Gameplay Ability System in UE5 By Stephen Ulibarri

#include "AbilitySystem/CC_AttributeSet.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "GameplayTags/CCTags.h"
#include "Net/UnrealNetwork.h"

void UCC_AttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, MaxMana, COND_None, REPNOTIFY_Always);
	
	DOREPLIFETIME(ThisClass, bAttributeInitialized);
}

void UCC_AttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	if (!bAttributeInitialized)
	{
		bAttributeInitialized = true;
		OnAttributeInitialized.Broadcast();
	}
	
	if (Data.EvaluatedData.Attribute == GetHealthAttribute() && GetHealth() <= 0.f)
	{
		FGameplayEventData Payload;
		Payload.Instigator = Data.Target.GetAvatarActor(); // who received the hit "enemy"
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor
			(/*AActor* who cause the damage "Player"*/ Data.EffectSpec.GetEffectContext().GetInstigator(),CCTags::Events::KillScored, Payload);
		
	}
}

void UCC_AttributeSet::OnRep_AttributeInitialized()
{
	if (bAttributeInitialized)
	{
		OnAttributeInitialized.Broadcast();
	}
}

void UCC_AttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Health, OldValue);
}

void UCC_AttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, MaxHealth, OldValue);
}

void UCC_AttributeSet::OnRep_Mana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Mana, OldValue);
}

void UCC_AttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, MaxMana, OldValue);
}
