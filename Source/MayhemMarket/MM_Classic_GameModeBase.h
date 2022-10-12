// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MayhemMarketGameModeBase.h"
#include "MM_Classic_GameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class MAYHEMMARKET_API AMM_Classic_GameModeBase : public AMayhemMarketGameModeBase
{
	GENERATED_BODY()

public: 

	virtual void StartPlay() override;
	


};
