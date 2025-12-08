// Copyrights to Mahdi94x based on Course Make exciting multiplayer and single player games with the Gameplay Ability System in UE5 By Stephen Ulibarri

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "CC_AttributeChangeTask.generated.h"

struct FOnAttributeChangeData;
class UAbilitySystemComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnAttributeChanged, FGameplayAttribute, Attribute, float, OldValue,
                                               float, NewValue);

UCLASS(BlueprintType, meta = (ExposedAsyncProxy = "AsyncTask"))
class PROJECT_GAS_CC_API UCC_AttributeChangeTask : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(BlueprintAssignable) // delegate instance
	FOnAttributeChanged OnAttributeChanged;
	
	UFUNCTION(BlueprintCallable, meta = (BlueprintInternalUseOnly = "true")) // implementation detail for the node
	static UCC_AttributeChangeTask* ListenForAttributeChange(UAbilitySystemComponent* AbilitySystemComponent, FGameplayAttribute Attribute);
	
	UFUNCTION(BlueprintCallable) // clean up the task and avoid any memory leaks
	void EndTask();
	
	/*Member Variables*/
	TWeakObjectPtr<UAbilitySystemComponent> Asc;
	FGameplayAttribute AttributeToListenFor;
	
	void AttributeChange(const FOnAttributeChangeData& Data) const; //Callback function responsible for broadcasting the new values
};
