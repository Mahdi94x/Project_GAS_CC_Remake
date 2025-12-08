// Copyrights to Mahdi94x based on Course Make exciting multiplayer and single player games with the Gameplay Ability System in UE5 By Stephen Ulibarri

#include "GameObjects/CC_Projectile.h"
#include "Characters/CC_PlayerCharacter.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "AbilitySystemComponent.h"

ACC_Projectile::ACC_Projectile()
{
	PrimaryActorTick.bCanEverTick = false;
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
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
	
	const FGameplayEffectContextHandle ContextHandle = PlayerAbilitySystemComponent->MakeEffectContext();
	const FGameplayEffectSpecHandle SpecHandle = PlayerAbilitySystemComponent->MakeOutgoingSpec(DamageEffect, 1.f, ContextHandle);
	// TODO: use the damage variable for the amount of damage to cause 
	PlayerAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	
	SpawnImpactEffects();
	Destroy();
}



