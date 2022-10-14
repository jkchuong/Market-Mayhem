// Fill out your copyright notice in the Description page of Project Settings.


#include "MM_Classic_GameModeBase.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "ShopperPlayerController.h"


void AMM_Classic_GameModeBase::StartPlay()
{
    Super::StartPlay();


}

void AMM_Classic_GameModeBase::EndGame(float Score)
{
    Super::EndGame(Score);

    // TODO: Sort the top 3 scores then pass to player controller to display

    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    
    if (PlayerController)
    {
        PlayerController->GameHasEnded(PlayerController->GetPawn(), true);
        AShopperPlayerController* ShopperPlayerController = Cast<AShopperPlayerController>(PlayerController);
        if (ShopperPlayerController)
        {
            ShopperPlayerController->Score = Score;

            UE_LOG(LogTemp, Warning, TEXT("Score for %s: %f"), *ShopperPlayerController->GetPawn()->GetName(), Score);
        }
    }
     
}