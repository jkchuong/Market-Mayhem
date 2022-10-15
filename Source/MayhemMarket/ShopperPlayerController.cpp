// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopperPlayerController.h"

#include "Blueprint/UserWidget.h"
#include "ShopperCharacter.h"
#include "EngineUtils.h"

void AShopperPlayerController::BeginPlay()
{
    Super::BeginPlay();

    StartScreen = CreateWidget(this, StartScreenClass);
    if (StartScreen)
    {
        StartScreen->AddToViewport();
    }

    SetShowMouseCursor(true);

    // Stop everyone from starting the round at the start
    for (AShopperCharacter* Shopper : TActorRange<AShopperCharacter>(GetWorld()))
    {
        Shopper->bCanMove = false;
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

void AShopperPlayerController::BeginGame()
{
    if (StartScreen)
    {
        StartScreen->RemoveFromViewport();
    }

    SetShowMouseCursor(false);

    for (AShopperCharacter* Shopper : TActorRange<AShopperCharacter>(GetWorld()))
    {
        // Don't let anyone move until the delay before the round has begun. Only want timer on the actual player character.
        GetWorldTimerManager().SetTimer(DelayInputTimerHandle, FTimerDelegate::CreateLambda([Shopper]{
            Shopper->bCanMove = true;
            if (Shopper->IsPlayerControlled())
            {
                Shopper->OpenShop();
            }
        }), TimeToBegin, false);
    }

    HUDScreen = CreateWidget(this, HUDScreenClass);
    if (HUDScreen)
    {
        HUDScreen->AddToViewport();
    }
}