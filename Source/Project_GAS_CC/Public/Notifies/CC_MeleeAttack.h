// Copyrights to Mahdi94x based on Course Make exciting multiplayer and single player games with the Gameplay Ability System in UE5 By Stephen Ulibarri

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "CC_MeleeAttack.generated.h"

UCLASS()
class PROJECT_GAS_CC_API UCC_MeleeAttack : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;

private:
	
	TArray<FHitResult> PerformSphereTrace(USkeletalMeshComponent* MeshComp);
	void SendEventsToActors(USkeletalMeshComponent* MeshComp, const TArray<FHitResult>& Hits) const;
	
	UPROPERTY(EditAnywhere, Category = "Crash|Debug")
	bool bDrawDebug = true;
	
	UPROPERTY(EditAnywhere, Category = "Crash|Socket")
	FName SocketName{"FX_Trail_01_R"};
	
	UPROPERTY(EditAnywhere, Category = "Crash|Socket")
	float SocketExtensionOffset{40.f};
	
	UPROPERTY(EditAnywhere, Category = "Crash|Socket")
	float SphereTraceRadius{60.f};
};
