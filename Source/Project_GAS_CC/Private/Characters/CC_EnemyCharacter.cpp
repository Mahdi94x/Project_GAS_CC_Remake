// Copyrights to Mahdi94x based on Course Make exciting multiplayer and single player games with the Gameplay Ability System in UE5 By Stephen Ulibarri

#include "Characters/CC_EnemyCharacter.h"
#include "AbilitySystem/CC_AbilitySystemComponent.h"
#include "AbilitySystem/CC_AttributeSet.h"
#include "AIController.h"


ACC_EnemyCharacter::ACC_EnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	AbilitySystemComponent = CreateDefaultSubobject<UCC_AbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	
	AttributeSet = CreateDefaultSubobject<UCC_AttributeSet>("AttributeSet");

}

UAbilitySystemComponent* ACC_EnemyCharacter::GetAbilitySystemComponent() const
{
	return this->AbilitySystemComponent;
}

UAttributeSet* ACC_EnemyCharacter::GetAttributeSet() const
{
	return this->AttributeSet;
}

void ACC_EnemyCharacter::HandleDeath()
{
	Super::HandleDeath();
	
	AAIController* AIController = GetController<AAIController>();
	if (!IsValid(AIController)) return;
	
	AIController->StopMovement();
	
}

void ACC_EnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (!IsValid(GetAbilitySystemComponent())) return;
	GetAbilitySystemComponent()->InitAbilityActorInfo(this,this);
	OnASCInitialized.Broadcast(GetAbilitySystemComponent(), GetAttributeSet());
	
	if (!HasAuthority()) return;
	
	GiveStartUpAbilities();
	InitializeAttributes();
	
	const UCC_AttributeSet* CC_AttributeSet = Cast<UCC_AttributeSet>(GetAttributeSet());
	if (!IsValid(CC_AttributeSet)) return;
	
	GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(CC_AttributeSet->GetHealthAttribute())
		.AddUObject(this, &ThisClass::OnHealthChanged);
	
}

