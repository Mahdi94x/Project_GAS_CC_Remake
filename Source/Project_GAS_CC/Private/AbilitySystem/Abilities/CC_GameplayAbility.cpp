// Copyrights to Mahdi94x based on Course Make exciting multiplayer and single player games with the Gameplay Ability System in UE5 By Stephen Ulibarri

#include "AbilitySystem/Abilities/CC_GameplayAbility.h"

void UCC_GameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	if (bDrawDebugs && GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1,3.f,FColor::Cyan, 
			FString::Printf(TEXT("%s Activated"),*GetName()));
	}
}
