// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_GetRandomLocation.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

UBTTask_GetRandomLocation::UBTTask_GetRandomLocation()
{
    NodeName = TEXT("Get Random Location");
}

EBTNodeResult::Type UBTTask_GetRandomLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    AICurrentLocation = OwnerComp.GetAIOwner()->GetPawn()->GetActorLocation();

    UNavigationSystemV1* NavArea = FNavigationSystem::GetCurrent<UNavigationSystemV1>(this);
    if (NavArea)
    {
        FVector RandomTargetLocation = NavArea->GetRandomPointInNavigableRadius(this, AICurrentLocation, SearchRadius);
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), RandomTargetLocation);
    }

    return EBTNodeResult::Succeeded;
}