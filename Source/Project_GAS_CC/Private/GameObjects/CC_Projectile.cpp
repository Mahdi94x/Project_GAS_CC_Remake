// Copyrights to Mahdi94x based on Course Make exciting multiplayer and single player games with the Gameplay Ability System in UE5 By Stephen Ulibarri

#include "GameObjects/CC_Projectile.h"
#include "Characters/CC_PlayerCharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "AbilitySystemComponent.h"
#include "GameplayTags/CCTags.h"
#include "Utils/CC_BlueprintLibrary.h"

ACC_Projectile::ACC_Projectile()
{
	PrimaryActorTick.bCanEverTick = false;
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	bReplicates = true;
}

void ACC_Projectile::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	
	ACC_PlayerCharacter* PlayerCharacter = Cast<ACC_PlayerCharacter>(OtherActor);
	if (!IsValid(PlayerCharacter)) return;
	if (!PlayerCharacter->IsAlive()) return;
	
	UAbilitySystemComponent* PlayerAbilitySystemComponent = PlayerCharacter->GetAbilitySystemComponent();
	if (!IsValid(PlayerAbilitySystemComponent) || !HasAuthority()) return;
	
	FGameplayEventData Payload;
	Payload.Instigator = this->GetOwner();
	Payload.Target = PlayerCharacter;
	UCC_BlueprintLibrary::SendDamageEventToPlayer(PlayerCharacter,DamageGameplayEffect, Payload, CCTags::SetByCaller::Projectile,ProjectileDamage);
	
	SpawnImpactEffects();
	Destroy();
}



