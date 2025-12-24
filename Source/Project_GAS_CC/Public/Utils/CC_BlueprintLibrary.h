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
	static FClosestActorWithTagResult FindClosestActorWithTag(UObject* WorldContextObject, const FVector& Origin, const FName& Tag, float SearchRange);
	
	UFUNCTION(BlueprintCallable)
	static void SendDamageEventToPlayer(AActor* Target, const TSubclassOf<UGameplayEffect>& DamageEffect, UPARAM(ref) FGameplayEventData& Payload, const FGameplayTag& SetByCallerTag, float Damage, const FGameplayTag& EventTagOverride, UObject* OptionalParticleSystem = nullptr);
	
	UFUNCTION(BlueprintCallable, Category = "Crash|Abilities")
	static TArray<AActor*> HitBoxOverlapTest(AActor* AvatarActor , float HitBoxRadius, float HitBoxForwardOffset = 0.f, float HitBoxElevationOffset = 0.f, bool bDrawDebugs = false);
	
	static void DrawHitBoxOverlapDebugs(UObject* WorldContextObject, const TArray<FOverlapResult>& OverlapResults , const FVector& HitBoxLocation, float HitBoxRadius);
	
	UFUNCTION(BlueprintCallable, Category = "Crash|Abilities")
	static TArray<AActor*> ApplyKnockback(AActor* AvatarActor, const TArray<AActor*>& HitActors, float InnerRadius, float OuterRadius, float LaunchForceMagnitude, float RotationAngle = 45.f, bool bDrawDebugs = false);
	
	UFUNCTION(BlueprintCallable)
	static void SendDamageEventToPlayers(TArray<AActor*> Targets, const TSubclassOf<UGameplayEffect>& DamageEffect, UPARAM(ref) FGameplayEventData& Payload, const FGameplayTag& SetByCallerTag, float Damage, const FGameplayTag& EventTagOverride, UObject* OptionalParticleSystem = nullptr);
	
};
