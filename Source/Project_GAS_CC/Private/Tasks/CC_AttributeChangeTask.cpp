// Copyrights to Mahdi94x based on Course Make exciting multiplayer and single player games with the Gameplay Ability System in UE5 By Stephen Ulibarri

#include "Tasks/CC_AttributeChangeTask.h"
#include "AbilitySystemComponent.h"

UCC_AttributeChangeTask* UCC_AttributeChangeTask::ListenForAttributeChange( UAbilitySystemComponent* AbilitySystemComponent, FGameplayAttribute Attribute)
{
	// creating the node
	UCC_AttributeChangeTask* WaitForAttributeChangeTask = NewObject<UCC_AttributeChangeTask>();
	
	// setting the TWeakObjectPtr
	WaitForAttributeChangeTask->Asc = AbilitySystemComponent;
	WaitForAttributeChangeTask->AttributeToListenFor = Attribute;
	
	// Checking the validity of the AbilitySystemComponent
	if (!IsValid(AbilitySystemComponent))
	{
		WaitForAttributeChangeTask->RemoveFromRoot(); // remove if ASC is not valid
		return nullptr;
	}
	
	// binding the task to the delegate that the ASC fires when an attribute change
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Attribute)
		.AddUObject(WaitForAttributeChangeTask,&UCC_AttributeChangeTask::AttributeChange);
	
	return WaitForAttributeChangeTask;
}

void UCC_AttributeChangeTask::EndTask()
{
	if (Asc.IsValid())
	{
		Asc->GetGameplayAttributeValueChangeDelegate(AttributeToListenFor).RemoveAll(this);
	}
	SetReadyToDestroy();
	MarkAsGarbage();
}

void UCC_AttributeChangeTask::AttributeChange(const FOnAttributeChangeData& Data) const
{
	OnAttributeChanged.Broadcast(Data.Attribute, Data.OldValue, Data.NewValue);
}
