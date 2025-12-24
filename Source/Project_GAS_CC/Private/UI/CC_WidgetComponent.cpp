// Copyrights to Mahdi94x based on Course Make exciting multiplayer and single player games with the Gameplay Ability System in UE5 By Stephen Ulibarri

#include "UI/CC_WidgetComponent.h"
#include "AbilitySystem/CC_AbilitySystemComponent.h"
#include "AbilitySystem/CC_AttributeSet.h"
#include "Blueprint/WidgetTree.h"
#include "Characters/CC_BaseCharacter.h"
#include "UI/CC_AttributeWidget.h"

void UCC_WidgetComponent::BeginPlay()
{
	Super::BeginPlay();
	
	InitAbilitySystemData();
	
	if (!IsASCInitialized())
	{
		CrashCharacter->OnASCInitialized.AddDynamic(this, &ThisClass::OnASCInitialized);
		return;
	}
	InitializeAttributeDelegate();
}

void UCC_WidgetComponent::InitAbilitySystemData()
{
	CrashCharacter = Cast<ACC_BaseCharacter>(GetOwner());
	AttributeSet = Cast<UCC_AttributeSet>(CrashCharacter->GetAttributeSet());
	AbilitySystemComponent = Cast<UCC_AbilitySystemComponent>(CrashCharacter->GetAbilitySystemComponent());
}

bool UCC_WidgetComponent::IsASCInitialized() const
{
	return AbilitySystemComponent.IsValid() && AttributeSet.IsValid();
}

void UCC_WidgetComponent::OnASCInitialized(UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	AttributeSet = Cast<UCC_AttributeSet>(AS);
	AbilitySystemComponent = Cast<UCC_AbilitySystemComponent>(ASC);
	
	if (!IsASCInitialized()) return;
	InitializeAttributeDelegate();
}

void UCC_WidgetComponent::InitializeAttributeDelegate()
{
	if (!AttributeSet->bAttributeInitialized)
	{
		AttributeSet->OnAttributeInitialized.AddDynamic(this, &ThisClass::BindToAttributeChanged);
	}
	else
	{
		BindToAttributeChanged();
	}
}

void UCC_WidgetComponent::BindToAttributeChanged()
{
	for (const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair : AttributeMap)
	{
		BindWidgetToAttributeChanged(GetUserWidgetObject(), Pair);
		
		GetUserWidgetObject()->WidgetTree->ForEachWidget([this, &Pair](UWidget* ChildWidget)
		{
			BindWidgetToAttributeChanged(ChildWidget, Pair);
		});
	}
}

void UCC_WidgetComponent::BindWidgetToAttributeChanged(UWidget* WidgetObject,
	const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair) const
{
	UCC_AttributeWidget* AttributeWidget = Cast<UCC_AttributeWidget>(WidgetObject);
		
	if (!IsValid(AttributeWidget)) return; // Only care about CC_Attribute_Widget
	if (!AttributeWidget->MatchesAttributes(Pair)) return; // Only subscribe for matching attributes this->TMap vs TTuple
	AttributeWidget->AvatarActor = 	CrashCharacter;
	
	AttributeWidget->OnAttributeChange(Pair, AttributeSet.Get(), 0.f); // Setting Initial Values
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Key).AddLambda
	([this,AttributeWidget, &Pair](const FOnAttributeChangeData& AttributeChangeData)
	{
		AttributeWidget->OnAttributeChange(Pair, AttributeSet.Get(), AttributeChangeData.OldValue); // Update during gameplay
	});
}







