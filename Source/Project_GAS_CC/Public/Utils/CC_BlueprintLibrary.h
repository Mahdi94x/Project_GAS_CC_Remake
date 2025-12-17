// Copyrights to Mahdi94x based on Course Make exciting multiplayer and single player games with the Gameplay Ability System in UE5 By Stephen Ulibarri

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CC_BlueprintLibrary.generated.h"

class UGameplayEffect;
struct FGameplayTag;
struct FGameplayEventData;

UENUM(BlueprintType)
enum class EHitDirection : uint8
{
	Left,
	Right,
	Back,
	Forward
};

USTRUCT(BlueprintType)
struct FClosestActorWithTagResult
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadOnly)
	 TWeakObjectPtr<AActor> Actor = nullptr;
	
	UPROPERTY(BlueprintReadOnly)
	float Distance = -1.f;
	
};

UCLASS()
class PROJECT_GAS_CC_API UCC_BlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure)
	static EHitDirection GetHitDirection(const FVector& TargetForward, const FVector& ToInstigator);
	
	UFUNCTION(BlueprintPure)
	static FName GetHitDirectionName (const EHitDirection HitDirection);
	
	UFUNCTION(BlueprintCallable)
	static FClosestActorWithTagResult FindClosestActorWithTag(const UObject* WorldContextObject, const FVector& Origin, const FName& Tag);
	
	UFUNCTION(BlueprintCallable)
	static void SendDamageEventToPlayer(AActor* Target, const TSubclassOf<UGameplayEffect>& DamageEffect, UPARAM(ref) FGameplayEventData& Payload, const FGameplayTag& DataTag, float Damage, UObject* OptionalParticleSystem = nullptr);
	
	
	
};
