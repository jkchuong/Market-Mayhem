// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MayhemMarketGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class MAYHEMMARKET_API AMayhemMarketGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public: 

	virtual void EndGame(float Score);

};
