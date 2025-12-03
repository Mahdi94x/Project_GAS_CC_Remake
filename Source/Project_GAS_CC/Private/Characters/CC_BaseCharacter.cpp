// Copyrights to Mahdi94x based on Course Make exciting multiplayer and single player games with the Gameplay Ability System in UE5 By Stephen Ulibarri

#include "Project_GAS_CC/Public/Characters/CC_BaseCharacter.h"
#include "AbilitySystemComponent.h"
#include "GameplayAbilitySpec.h"
#include "Net/UnrealNetwork.h"

namespace CrashTags
{
	const FName Player = FName("Player");
}

ACC_BaseCharacter::ACC_BaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
	// Tick and refresh bone transform whether rendered or not - for bone updates on a dedicated server
	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
}

void ACC_BaseCharacter::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ThisClass, bAlive);
}

UAbilitySystemComponent* ACC_BaseCharacter::GetAbilitySystemComponent() const
{
	return nullptr;
}

void ACC_BaseCharacter::GiveStartUpAbilities()
{
	if (!IsValid(GetAbilitySystemComponent())) return;
	
	for (const TSubclassOf<UGameplayAbility>& Ability : StartUpAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability);
		GetAbilitySystemComponent()->GiveAbility(AbilitySpec);
	}
}

void ACC_BaseCharacter::InitializeAttributes() const
{
	checkf(IsValid(InitializeAttributeEffect), TEXT("InitializeAttributeSet not set."));
	
	ApplyingGameplayEffect(InitializeAttributeEffect);
}

void ACC_BaseCharacter::ResetAttributes() const
{
	checkf(IsValid(ResetAttributeEffect), TEXT("ResetAttributeEffect not set."));
	
	ApplyingGameplayEffect(ResetAttributeEffect);
}

void ACC_BaseCharacter::OnHealthChanged(const FOnAttributeChangeData& AttributeChangeData)
{
	if (AttributeChangeData.NewValue <= 0.f)
	{
		HandleDeath();
	}
	
}

void ACC_BaseCharacter::HandleDeath()
{
	bAlive = false;
}

void ACC_BaseCharacter::ApplyingGameplayEffect(const TSubclassOf<UGameplayEffect>& GameplayEffect) const
{
	const FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	const FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(GameplayEffect,1.f,ContextHandle);
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}

void ACC_BaseCharacter::HandleRespawn()
{
	bAlive = true;
}



