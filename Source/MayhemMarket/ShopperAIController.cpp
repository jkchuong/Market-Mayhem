// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopperAIController.h"

#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShopperCharacter.h"


void AShopperAIController::BeginPlay()
{
    Super::BeginPlay();

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    if (AIBehavior && PlayerPawn)
    {
        RunBehaviorTree(AIBehavior);
        BlackboardComponent = GetBlackboardComponent();

        // Initialize with locations and lists of all item zones in the area -> Don't need to constantly find it during gameplay


	}    

}