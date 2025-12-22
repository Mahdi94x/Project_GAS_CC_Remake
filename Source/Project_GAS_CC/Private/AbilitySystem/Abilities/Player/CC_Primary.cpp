// Copyrights to Mahdi94x based on Course Make exciting multiplayer and single player games with the Gameplay Ability System in UE5 By Stephen Ulibarri

#include "AbilitySystem/Abilities/Player/CC_Primary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayTags/CCTags.h"

void UCC_Primary::SendHitReactEventsToActor(const TArray<AActor*>& ActorsHit)
{
	if (ActorsHit.Num() == 0) return;
	
	for (AActor* HitActor : ActorsHit)
	{
		FGameplayEventData Payload;
		Payload.Instigator = GetAvatarActorFromActorInfo();
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(HitActor,CCTags::Events::Enemy::HitReact,Payload);
		
	}
}

