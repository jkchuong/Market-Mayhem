// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopperPlayerController.h"

#include "Blueprint/UserWidget.h"
#include "ShopperCharacter.h"
#include "EngineUtils.h"
#include "UpgradesSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "ItemZone.h"

AShopperPlayerController::AShopperPlayerController()
{

}

void AShopperPlayerController::BeginPlay()
{
    Super::BeginPlay();

    // Initialize the array with valid screens
    BackgroundScreen = CreateWidget(this, BackgroundScreenClass);
    StartScreen = CreateWidget(this, StartScreenClass);
    EndScreen = CreateWidget(this, EndScreenClass);
    HUDScreen = CreateWidget(this, HUDScreenClass);
    UpgradeScreen = CreateWidget(this, UpgradeScreenClass);
    CreditsScreen = CreateWidget(this, CreditsScreenClass);

    AllScreens.Add(StartScreen);
    AllScreens.Add(HUDScreen);
    AllScreens.Add(EndScreen);
    AllScreens.Add(UpgradeScreen);
    AllScreens.Add(CreditsScreen);

    if (BackgroundScreen)
    {
        BackgroundScreen->AddToViewport();
    }  

    ChangeScreenTo(StartScreen);

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

    ChangeScreenTo(EndScreen);

    SetShowMouseCursor(true);

    // Get saved game to add points from the score 
    if (UUpgradesSaveGame* LoadedGame = Cast<UUpgradesSaveGame>(UGameplayStatics::LoadGameFromSlot(TEXT("Player1"), 0)))
    {
        LoadedGame->Points += PlayerScore;
        UGameplayStatics::SaveGameToSlot(LoadedGame, LoadedGame->SaveSlotName, 0);
    }

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
        
        ReturnString += FString::FromInt(FMath::Floor(Score));
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

    if (BackgroundScreen)
    {
        BackgroundScreen->RemoveFromViewport();
    }

    SetShowMouseCursor(false);

    for (AShopperCharacter* Shopper : TActorRange<AShopperCharacter>(GetWorld()))
    {
        // Don't let anyone move until the delay before the round has begun. Only want timer on the actual player character.
        GetWorldTimerManager().SetTimer(DelayInputTimerHandle, FTimerDelegate::CreateLambda([Shopper]{
            Shopper->bCanMove = true;
            Shopper->OpenShop();
        }), TimeToBegin, false);
    }

    if (HUDScreen)
    {
        HUDScreen->AddToViewport();
    }
}

void AShopperPlayerController::ApplySaveToPlayer(UUpgradesSaveGame* SavedGame)
{
    for (AShopperCharacter* Shopper : TActorRange<AShopperCharacter>(GetWorld()))
    {
        Shopper->SetPlayerFinalStats(SavedGame);
    }

    for (AItemZone* ItemZone : TActorRange<AItemZone>(GetWorld()))
    {
        ItemZone->SetFinalStats(SavedGame);
    }
}

void AShopperPlayerController::OnClickUpgrade()
{
    ChangeScreenTo(UpgradeScreen);
}

void AShopperPlayerController::OnClickCredits()
{
    ChangeScreenTo(CreditsScreen);
}

void AShopperPlayerController::OnClickReturn()
{
    ChangeScreenTo(StartScreen);
}

void AShopperPlayerController::OnClickQuit()
{
    UKismetSystemLibrary::QuitGame(this, this, EQuitPreference::Quit, false);
}

void AShopperPlayerController::ChangeScreenTo(UUserWidget* ScreenToChangeTo)
{
    // Reusable function to disable all the screens and only reenable the one we want showing.
    for (UUserWidget* Screen : AllScreens)
    {
        if (Screen)
        {
            Screen->RemoveFromViewport();
        }
    }

    if (ScreenToChangeTo)
    {
        ScreenToChangeTo->AddToViewport();
    }

}

int AShopperPlayerController::GetUpgradeCostFromLevel(int UpgradeLevel) const
{
    return FMath::Floor(BaseUpgradeCost * (FMath::Pow(RateUpgradeIncrease, UpgradeLevel)));
}

bool AShopperPlayerController::IsUpgradeScreenDisplayed() const
{
    return UpgradeScreen->IsInViewport();
}