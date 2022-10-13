// Fill out your copyright notice in the Description page of Project Settings.


#include "MM_Classic_GameModeBase.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void AMM_Classic_GameModeBase::StartPlay()
{
    Super::StartPlay();


}

void AMM_Classic_GameModeBase::EndGame(float Score)
{
    Super::EndGame(Score);
    UE_LOG(LogTemp, Warning, TEXT("In GameModeBase"));
    // Call player controller with the score here and tally up everyones score to display.

    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    PlayerController->GameHasEnded(PlayerController->GetPawn(), true);

}