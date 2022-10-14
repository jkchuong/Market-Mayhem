// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_GetItemZoneLocation.h"

#include "ShopperCharacter.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShoppingCart.h"
#include "ItemZone.h"
#include "Item.h"
#include "EngineUtils.h"

UBTTask_GetItemZoneLocation::UBTTask_GetItemZoneLocation()
{
    NodeName = "Get Next Item Zone Location";
}


EBTNodeResult::Type UBTTask_GetItemZoneLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    FString RequiredItemName = OwnerComp.GetBlackboardComponent()->GetValueAsString(TEXT("RequiredItemName"));
    FVector ItemZoneDestination;

    // Find the correct item zone by looping through the actors and looking for it.
    for (AItemZone* ItemZone : TActorRange<AItemZone>(GetWorld()))
    {
        FString ItemZoneType = ItemZone->GetItem()->ItemName;
        if (RequiredItemName == ItemZoneType)
        {
            OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), ItemZone->GetActorLocation());
            return EBTNodeResult::Succeeded;
        }
    }

    return EBTNodeResult::Failed;
}