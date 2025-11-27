// Copyrights to Mahdi94x based on Course Make exciting multiplayer and single player games with the Gameplay Ability System in UE5 By Stephen Ulibarri

#include "AbilitySystem/Abilities/Enemy/CC_HitReact.h"

void UCC_HitReact::CacheHitDirectionVectors(AActor* Instigator)
{
	AvatarForward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	
	const FVector AvatarLocation = GetAvatarActorFromActorInfo()->GetActorLocation();
	const FVector InstigatorLocation = Instigator->GetActorLocation();
	
	ToInstigator = (InstigatorLocation - AvatarLocation).GetSafeNormal();
}
