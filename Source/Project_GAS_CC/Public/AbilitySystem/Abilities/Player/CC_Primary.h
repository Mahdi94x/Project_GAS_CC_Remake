// Copyrights to Mahdi94x based on Course Make exciting multiplayer and single player games with the Gameplay Ability System in UE5 By Stephen Ulibarri

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/CC_GameplayAbility.h"
#include "CC_Primary.generated.h"

UCLASS()
class PROJECT_GAS_CC_API UCC_Primary : public UCC_GameplayAbility
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "Crash|Abilities")
	void SendHitReactEventsToActor(const TArray<AActor*>& ActorsHit);
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Crash|Abilities")
	float HitBoxRadius = 100.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Crash|Abilities")
	float HitBoxForwardOffset = 200.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Crash|Abilities")
	float HitBoxElevationOffset = 20.f;
	
};
