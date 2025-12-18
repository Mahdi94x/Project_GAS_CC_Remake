// Copyrights to Mahdi94x based on Course Make exciting multiplayer and single player games with the Gameplay Ability System in UE5 By Stephen Ulibarri

#include "AbilitySystem/Abilities/Enemy/CC_HitReact.h"

void UCC_HitReact::CacheHitDirectionVectors(AActor* Instigator)
{
	if (!IsInstantiated()) return;
	AActor* AvatarActor = GetAvatarActorFromActorInfo();
	if (!IsValid(AvatarActor) || !IsValid(Instigator)) return;
	
	AvatarForward = AvatarActor->GetActorForwardVector();
	const FVector AvatarLocation = AvatarActor->GetActorLocation();
	const FVector InstigatorLocation = Instigator->GetActorLocation();

	ToInstigator = (InstigatorLocation - AvatarLocation).GetSafeNormal();
}
