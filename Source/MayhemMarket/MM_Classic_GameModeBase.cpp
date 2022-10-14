// Fill out your copyright notice in the Description page of Project Settings.


#include "MM_Classic_GameModeBase.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "ShopperCharacter.h"
#include "ShopperPlayerController.h"
#include "ShopperAIController.h"
#include "EngineUtils.h"

void AMM_Classic_GameModeBase::StartPlay()
{
    Super::StartPlay();


}

void AMM_Classic_GameModeBase::EndGame(float Score)
{
    Super::EndGame(Score);

    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    AShopperPlayerController* ShopperPlayerController = Cast<AShopperPlayerController>(PlayerController);
    
    if (ShopperPlayerController)
    {
        // Get all the scores from all players in the world and sort by top three to show to UI
        TArray<float> AllScores;
        for (AShopperAIController* AIController : TActorRange<AShopperAIController>(GetWorld()))
        {
            AShopperCharacter* Shopper = Cast<AShopperCharacter>(AIController->GetPawn());
            AllScores.Add(Shopper->GetPlayerScore());
        }

        ShopperPlayerController->PlayerScore = Score;
        AllScores.Add(ShopperPlayerController->PlayerScore);
        AllScores.Sort([](const float& a, const float& b){return a > b;});
        AllScores.SetNum(3);
        ShopperPlayerController->TopScores = AllScores;

        ShopperPlayerController->GameHasEnded(ShopperPlayerController->GetPawn(), true);        
    }
     
}