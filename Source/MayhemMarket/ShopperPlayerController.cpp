// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopperPlayerController.h"

#include "Blueprint/UserWidget.h"

void AShopperPlayerController::BeginPlay()
{
    Super::BeginPlay();

    HUDScreen = CreateWidget(this, HUDScreenClass);
    if (HUDScreen)
    {
        HUDScreen->AddToViewport();
    }
}

void AShopperPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);

    UE_LOG(LogTemp, Warning, TEXT("In Controller"));

    HUDScreen->RemoveFromViewport();

    EndScreen = CreateWidget(this, EndScreenClass);
    EndScreen->AddToViewport();
}