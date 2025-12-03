// Copyrights to Mahdi94x based on Course Make exciting multiplayer and single player games with the Gameplay Ability System in UE5 By Stephen Ulibarri

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "CC_BaseCharacter.generated.h"

struct FOnAttributeChangeData;
class UGameplayEffect;
class UAttributeSet;
class UGameplayAbility;

namespace CrashTags
{
	extern PROJECT_GAS_CC_API const FName Player;
}

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FASCInitialized, UAbilitySystemComponent*, ASC, UAttributeSet*, AS);

UCLASS(Abstract)
class PROJECT_GAS_CC_API ACC_BaseCharacter : public ACharacter , public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ACC_BaseCharacter();
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	virtual UAttributeSet* GetAttributeSet() const {return nullptr;}
	bool IsAlive() const {return bAlive;} // Getter
	void SetAlive(bool bAliveStatus) {bAlive = bAliveStatus;} // Setter
	
	UFUNCTION(BlueprintCallable, Category = "Crash|Death")
	virtual void HandleRespawn();
	
	UPROPERTY(BlueprintAssignable)
	FASCInitialized OnASCInitialized;

	UFUNCTION(BlueprintCallable, Category = "Crash|Attributes")
	void ResetAttributes() const;
	
protected:
	void GiveStartUpAbilities();
	void InitializeAttributes() const;
	void OnHealthChanged(const FOnAttributeChangeData& AttributeChangeData);
	
	UFUNCTION(Category = "Crash|Death")
	virtual void HandleDeath();

private:
	void ApplyingGameplayEffect(const TSubclassOf<UGameplayEffect>& GameplayEffect) const;
	
	UPROPERTY(EditDefaultsOnly, Category = "Crash|Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartUpAbilities;
	
	UPROPERTY(EditDefaultsOnly, Category = "Crash|Effects")
	TSubclassOf<UGameplayEffect> InitializeAttributeEffect;
	
	UPROPERTY(EditDefaultsOnly, Category = "Crash|Effects")
	TSubclassOf<UGameplayEffect> ResetAttributeEffect;
	
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Replicated, Category = "Crash|Death", VisibleAnywhere)
	bool bAlive = true;

};
