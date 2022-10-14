// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_CheckShoppingList.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShopperCharacter.h"
#include "ShoppingCart.h"


UBTTask_CheckShoppingList::UBTTask_CheckShoppingList()
{
    NodeName = TEXT("Check Shopping List");
}

EBTNodeResult::Type UBTTask_CheckShoppingList::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    AShopperCharacter* Shopper = Cast<AShopperCharacter>(OwnerComp.GetAIOwner()->GetPawn());

    if (!Shopper)
    {
        return EBTNodeResult::Failed;
    }

    TMap<FString, int> ShoppingList = Shopper->GetShoppingList();
    TMap<FString, int> ShoppingCart = Shopper->ShoppingCart->GetStorage();

    // Shopping list is not complete if shopping cart either doesn't have the item, or there's not enough of the item

    bool bShoppingListCompleted{true};
    for (TPair<FString, int> ListItem : ShoppingList)
    {
        if (!ShoppingCart.Contains(ListItem.Key))
        {
            bShoppingListCompleted = false;
            break;
        }

        if (ShoppingCart[ListItem.Key] < ListItem.Value)
        {
            bShoppingListCompleted = false;
            break;
        }
    }

    OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), bShoppingListCompleted);

    return EBTNodeResult::Succeeded;

}