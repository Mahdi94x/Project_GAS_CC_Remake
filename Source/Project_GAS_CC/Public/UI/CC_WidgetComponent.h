// Copyrights to Mahdi94x based on Course Make exciting multiplayer and single player games with the Gameplay Ability System in UE5 By Stephen Ulibarri

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "Components/WidgetComponent.h"
#include "CC_WidgetComponent.generated.h"

class UAbilitySystemComponent;
class UCC_AttributeSet;
class UCC_AbilitySystemComponent;
class ACC_BaseCharacter;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECT_GAS_CC_API UCC_WidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:


protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditAnywhere, Category= "Crash|UI")
	TMap<FGameplayAttribute, FGameplayAttribute> AttributeMap;
	
private:
	void InitAbilitySystemData();
	
	bool IsASCInitialized() const;
	
	UFUNCTION()
	void OnASCInitialized(UAbilitySystemComponent* ASC , UAttributeSet* AS );
	
	void InitializeAttributeDelegate();
	
	UFUNCTION()
	void BindToAttributeChanged();
	
	void BindWidgetToAttributeChanged(UWidget* WidgetObject, const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair) const;
	
	TWeakObjectPtr<ACC_BaseCharacter> CrashCharacter;
	TWeakObjectPtr<UCC_AbilitySystemComponent> AbilitySystemComponent;
	TWeakObjectPtr<UCC_AttributeSet> AttributeSet;
	
	
	


};
