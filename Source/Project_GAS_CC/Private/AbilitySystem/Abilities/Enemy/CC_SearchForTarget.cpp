// Copyrights to Mahdi94x based on Course Make exciting multiplayer and single player games with the Gameplay Ability System in UE5 By Stephen Ulibarri

#include "AbilitySystem/Abilities/Enemy/CC_SearchForTarget.h"
#include "AbilitySystemComponent.h"
#include "Abilities/Async/AbilityAsync_WaitGameplayEvent.h"
#include "Abilities/Tasks/AbilityTask_WaitDelay.h"
#include "AIController.h"
#include "AbilitySystem/AbilitiyTask/CC_WaitGameplayEvent.h"
#include "Characters/CC_EnemyCharacter.h"
#include "GameplayTags/CCTags.h"
#include "Tasks/AITask_MoveTo.h"
#include "Utils/CC_BlueprintLibrary.h"

UCC_SearchForTarget::UCC_SearchForTarget()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerOnly;
}

void UCC_SearchForTarget::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	OwningEnemy = Cast<ACC_EnemyCharacter>(GetAvatarActorFromActorInfo());
	check (OwningEnemy.IsValid());
	OwningAIController = Cast<AAIController>(OwningEnemy->GetController());
	check (OwningAIController.IsValid());
	
	StartSearch();
	
	WaitGameplayEventTask = UCC_WaitGameplayEvent::WaitGameplayEventToActorProxy(GetAvatarActorFromActorInfo(),CCTags::Events::Enemy::EndAttack);
	WaitGameplayEventTask->EventReceived.AddDynamic(this, &ThisClass::UCC_SearchForTarget::EndAttackEventReceived);
	WaitGameplayEventTask->StartActivation();
	
}

void UCC_SearchForTarget::EndAttackEventReceived(FGameplayEventData Payload)
{
	StartSearch();
}

void UCC_SearchForTarget::StartSearch()
{
	if (bDrawDebugs) GEngine->AddOnScreenDebugMessage(-1,5.f,FColor::Red,
		FString::Printf(TEXT("UCC_SearchForTarget::StartSearch")));
	check(OwningEnemy.IsValid());
	
	const float SearchDelay = FMath::RandRange(OwningEnemy->MinAttackDelay, OwningEnemy->MaxAttackDelay);
	SearchDelayTask = UAbilityTask_WaitDelay::WaitDelay(this,SearchDelay);
	SearchDelayTask->OnFinish.AddDynamic(this, &ThisClass::UCC_SearchForTarget::SearchDelay);
	SearchDelayTask->Activate();
	
}

void UCC_SearchForTarget::SearchDelay()
{
	const FVector SearchOrigin = GetAvatarActorFromActorInfo()->GetActorLocation();
	FClosestActorWithTagResult ClosestActorResult = UCC_BlueprintLibrary::FindClosestActorWithTag(this, SearchOrigin,CrashTags::Player);
	
	TargetBaseCharacter = Cast<ACC_BaseCharacter>(ClosestActorResult.Actor);
	
	if (!TargetBaseCharacter.IsValid())
	{
		StartSearch();
		return;
	}
	if (TargetBaseCharacter->IsAlive())
	{
		MoveToTargetAndAttack();
	}
	else
	{
		StartSearch();
	}
}

void UCC_SearchForTarget::MoveToTargetAndAttack()
{
	if (!OwningEnemy.IsValid() || !OwningAIController.IsValid() || !TargetBaseCharacter.IsValid()) return;
	if (!OwningEnemy->IsAlive())
	{
		StartSearch();
		return;
	}
	
	MoveToLocationOrActorTask = UAITask_MoveTo::AIMoveTo(OwningAIController.Get(), FVector(),TargetBaseCharacter.Get(),OwningEnemy->AcceptanceRadius);
	MoveToLocationOrActorTask->OnMoveTaskFinished.AddUObject(this, &ThisClass::AttackTarget);
	MoveToLocationOrActorTask->ConditionalPerformMove();
}

void UCC_SearchForTarget::AttackTarget(TEnumAsByte<EPathFollowingResult::Type> Result, AAIController* AIController)
{
	if (!OwningEnemy.IsValid() || !TargetBaseCharacter.IsValid()) return;
	if (Result != EPathFollowingResult::Success)
	{
		StartSearch();
		return;
	}
	
	OwningEnemy->RotateToTarget(TargetBaseCharacter.Get());
	
	AttackDelayTask = UAbilityTask_WaitDelay::WaitDelay(this,OwningEnemy->GetTimelineLength());
	AttackDelayTask->OnFinish.AddDynamic(this, &ThisClass::UCC_SearchForTarget::Attack);
	AttackDelayTask->Activate();
}

void UCC_SearchForTarget::Attack()
{
	const FGameplayTag AttackTag = CCTags::CCAbilities::Enemy::Attack;
	
	GetAbilitySystemComponentFromActorInfo()->TryActivateAbilitiesByTag(AttackTag.GetSingleTagContainer());
}