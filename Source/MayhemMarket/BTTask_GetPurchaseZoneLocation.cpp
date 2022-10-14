// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_GetPurchaseZoneLocation.h"

#include "AIController.h"
#include "ShopperCharacter.h"
#include "PurchaseZone.h"
#include "EngineUtils.h"
#include "Math/NumericLimits.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTTask_GetPurchaseZoneLocation::UBTTask_GetPurchaseZoneLocation()
{
    NodeName = TEXT("Get Purchase Zone Location");
}

EBTNodeResult::Type UBTTask_GetPurchaseZoneLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    AShopperCharacter* Shopper = Cast<AShopperCharacter>(OwnerComp.GetAIOwner()->GetPawn());

    if (!Shopper)
    {
        return EBTNodeResult::Failed;
    }

    float ShortestDistanceToPurchaseZone = TNumericLimits<float>::Max();
    FVector ClosestPurchaseZone;

    for (APurchaseZone* PurchaseZone : TActorRange<APurchaseZone>(GetWorld()))
    {
        float DistanceToPurchaseZone = Shopper->GetDistanceTo(PurchaseZone);
        if (DistanceToPurchaseZone < ShortestDistanceToPurchaseZone)
        {
            ShortestDistanceToPurchaseZone = DistanceToPurchaseZone;
            ClosestPurchaseZone = PurchaseZone->GetActorLocation();
        }
    }

    OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), ClosestPurchaseZone);
    
    return EBTNodeResult::Succeeded;
}
