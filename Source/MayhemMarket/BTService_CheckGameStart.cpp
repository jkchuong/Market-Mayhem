// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_CheckGameStart.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ShopperCharacter.h"

UBTService_CheckGameStart::UBTService_CheckGameStart()
{
    NodeName = TEXT("Check Shop Open");
}

void UBTService_CheckGameStart::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    AShopperCharacter* ShopperCharacter = Cast<AShopperCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));

    if (ShopperCharacter)
    {
        bool bShopOpen = ShopperCharacter->IsShopOpen();
        OwnerComp.GetBlackboardComponent()->SetValueAsBool(GetSelectedBlackboardKey(), bShopOpen);
    }

}