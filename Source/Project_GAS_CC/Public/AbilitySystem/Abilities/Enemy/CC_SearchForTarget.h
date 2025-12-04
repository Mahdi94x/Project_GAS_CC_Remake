// Copyrights to Mahdi94x based on Course Make exciting multiplayer and single player games with the Gameplay Ability System in UE5 By Stephen Ulibarri

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/CC_GameplayAbility.h"
#include "CC_SearchForTarget.generated.h"

namespace EPathFollowingResult
{
	enum Type : int;
}

class UAITask_MoveTo;
class ACC_BaseCharacter;
class UAbilityTask_WaitDelay;
class UCC_WaitGameplayEvent;
class AAIController;
class ACC_EnemyCharacter;

UCLASS()
class PROJECT_GAS_CC_API UCC_SearchForTarget : public UCC_GameplayAbility
{
	GENERATED_BODY()
	
public:
	UCC_SearchForTarget();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	TWeakObjectPtr<ACC_EnemyCharacter> OwningEnemy;
	TWeakObjectPtr<AAIController> OwningAIController;
	TWeakObjectPtr<ACC_BaseCharacter> TargetBaseCharacter;
	
private:
	void StartSearch();
	
	UPROPERTY()
	TObjectPtr<UCC_WaitGameplayEvent> WaitGameplayEventTask;
	
	UPROPERTY()
	TObjectPtr<UAbilityTask_WaitDelay> SearchDelayTask; 
	
	UPROPERTY()
	TObjectPtr<UAITask_MoveTo> MoveToLocationOrActorTask;
	
	UPROPERTY()
	TObjectPtr<UAbilityTask_WaitDelay> AttackDelayTask;
	
	UFUNCTION()
	void EndAttackEventReceived(FGameplayEventData Payload);
	
	UFUNCTION()
	void SearchDelay();
	
	UFUNCTION()
	void AttackTarget(TEnumAsByte<EPathFollowingResult::Type> Result, AAIController* AIController);
	
	void MoveToTargetAndAttack();
	
	UFUNCTION()
	void Attack();
};
