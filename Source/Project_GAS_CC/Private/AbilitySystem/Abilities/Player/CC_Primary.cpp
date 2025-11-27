// Copyrights to Mahdi94x based on Course Make exciting multiplayer and single player games with the Gameplay Ability System in UE5 By Stephen Ulibarri

#include "AbilitySystem/Abilities/Player/CC_Primary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "Engine/OverlapResult.h"
#include "GameplayTags/CCTags.h"

TArray<AActor*> UCC_Primary::HitBoxOverlapTest()
{
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetAvatarActorFromActorInfo());
	
	// Ensure that the overlap test ignore the avatar actor
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActors(ActorsToIgnore);
	
	FCollisionResponseParams ResponseParams;
	ResponseParams.CollisionResponse.SetAllChannels(ECR_Ignore);
	ResponseParams.CollisionResponse.SetResponse(ECC_Pawn, ECR_Block);
	
	TArray<FOverlapResult> OverlapResults;
	FCollisionShape Sphere = FCollisionShape::MakeSphere(HitBoxRadius);
	
	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector() * HitBoxForwardOffset;
	const FVector HitboxLocation = GetAvatarActorFromActorInfo()->GetActorLocation() 
					+ Forward + FVector(0.f,0.f,HitBoxElevationOffset);
	
	GetWorld()->OverlapMultiByChannel(
		OverlapResults,
		HitboxLocation,
		FQuat::Identity,
		ECC_Visibility,
		Sphere,
		QueryParams,
		ResponseParams
		);
	
	TArray<AActor*> ActorsHit;
	for (const FOverlapResult& Result : OverlapResults)
	{
		if (!IsValid(Result.GetActor())) continue;
		
		ActorsHit.AddUnique(Result.GetActor());
	}
	
	if (bDrawDebugs)
	{
		DrawHitBoxOverlapDebugs(OverlapResults, HitboxLocation);
	}
	return ActorsHit;
}

void UCC_Primary::SendHitReactEventsToActor(const TArray<AActor*>& ActorsHit)
{
	if (ActorsHit.Num() == 0) return;
	
	for (AActor* HitActor : ActorsHit)
	{
		FGameplayEventData Payload;
		Payload.Instigator = GetAvatarActorFromActorInfo();
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(HitActor,CCTags::Events::Enemy::HitReact,Payload);
		
	}
}

void UCC_Primary::DrawHitBoxOverlapDebugs(const TArray<FOverlapResult>& OverlapResults, const FVector& HitBoxLocation) const
{
	DrawDebugSphere(GetWorld(), HitBoxLocation, HitBoxRadius, 24, FColor::Red, false, 5.f );
		
	for (const FOverlapResult& Result : OverlapResults)
	{
		if (IsValid(Result.GetActor()))
		{
			FVector DebugLocation = Result.GetActor()->GetActorLocation();
			DebugLocation.Z+=100.f;
			DrawDebugSphere(GetWorld(), DebugLocation, 30, 12, FColor::Green, false, 5.f );
		}
	}
}
