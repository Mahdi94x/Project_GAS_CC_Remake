// Copyrights to Mahdi94x based on Course Make exciting multiplayer and single player games with the Gameplay Ability System in UE5 By Stephen Ulibarri

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "CC_AbilitySystemComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_GAS_CC_API UCC_AbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	virtual void OnGiveAbility(FGameplayAbilitySpec& AbilitySpec) override;
	virtual void OnRep_ActivateAbilities() override;
	
	UFUNCTION(BlueprintCallable, Category = "Crash|Abilities")
	void SetAbilityLevel(TSubclassOf<UGameplayAbility> AbilityClass, int32 Level);
	
	UFUNCTION(BlueprintCallable, Category = "Crash|Abilities")
	void AddToAbilityLevel(TSubclassOf<UGameplayAbility> AbilityClass, int32 Level = 1);
	
private:
	void HandleAutoActivatedAbilities(const FGameplayAbilitySpec& AbilitySpec);
	
};
