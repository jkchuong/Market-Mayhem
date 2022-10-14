// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopperPlayerController.h"

#include "Blueprint/UserWidget.h"
#include "ShopperCharacter.h"

void AShopperPlayerController::BeginPlay()
{
    Super::BeginPlay();

    AShopperCharacter* Shopper = Cast<AShopperCharacter>(GetPawn());

    if (Shopper)
    {
        Shopper->bCanMove = false;

        // TODO: Move this to when the player clicks begin when start UI is done
        // Delay at the start of the game so the player isn't thrown into it immediately
        GetWorldTimerManager().SetTimer(DelayInputTimerHandle, FTimerDelegate::CreateLambda([Shopper]{
            Shopper->bCanMove = true;
            Shopper->OpenShop();
        }), TimeToBegin, false);
    }

    HUDScreen = CreateWidget(this, HUDScreenClass);
    if (HUDScreen)
    {
        HUDScreen->AddToViewport();
    }
}

void AShopperPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);

    HUDScreen->RemoveFromViewport();

    EndScreen = CreateWidget(this, EndScreenClass);
    EndScreen->AddToViewport();

    SetShowMouseCursor(true);
}

void AShopperPlayerController::ReturnToMenu()
{
    APlayerController::RestartLevel();
}

FString AShopperPlayerController::GetScoresAsFString() const
{
    FString ReturnString;

    for (float Score : TopScores)
    {
        ReturnString += FString::SanitizeFloat(Score);
		ReturnString += LINE_TERMINATOR;
    }

    return ReturnString;
}