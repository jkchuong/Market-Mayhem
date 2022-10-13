// Fill out your copyright notice in the Description page of Project Settings.


#include "MM_Classic_GameModeBase.h"

#include "Blueprint/UserWidget.h"

void AMM_Classic_GameModeBase::StartPlay()
{
    Super::StartPlay();


}

void AMM_Classic_GameModeBase::EndGame(float Score)
{
    Super::EndGame(Score);

    // Call player controller with the score here
    
}