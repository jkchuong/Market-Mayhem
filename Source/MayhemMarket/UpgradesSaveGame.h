// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "UpgradesSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class MAYHEMMARKET_API UUpgradesSaveGame : public USaveGame
{
	GENERATED_BODY()
	
public:

	UUpgradesSaveGame();

	/** The Name to save the file. As there will only be 1 player allowed, this will be automatically set to Player1.*/
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Basic)
    FString SaveSlotName{TEXT("Player1")};

	/** The index to save the file. As there will only be 1 player allowed, this will be automatically set to 0.*/
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = Basic)
    int UserIndex{0};

	/** Points gained from playing the game. Added from the final score and is used in the upgrade menu.*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Ugprades")
	int Points{0};

	/** The score multiplied for each item you purchase. Item Score = Score * (1.02 ^ Score Multiplier)).
	 *  Cost to upgrade will be Base * (1.41 ^ Level).
	*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Ugprades")
	int ScoreMultiplier{0};

	/** The movement speed of the player. Final movement speed = Base movement speed * (1.05 ^ Movement Upgrade). */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Ugprades")
	int Movement{0};

	/** The capacity of the shopping cart of the players. Final Capacity = Base Capacity + (5 * CartCapacity Upgrade).*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Ugprades")
	int CartCapacity{0};

	/** Increase of the number of items to take per second. Final TakeItemRate = Base TakeItemRate + TakeItemRate Upgrade.*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Ugprades")
	int TakeItemRate{0};
	
	/** Increase of the number of items purchased per second. Final PurchaseItemRate = Base PurchaseItemRate + PurchaseItemRate Upgrade.*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Ugprades")
	int PurchaseItemRate{0};

	/** The capacity of the item zones. Final Capacity = Base Capacity + (10 * ItemZoneCapacity Upgrade).*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Ugprades")
	int ItemZoneCapacity{0};

	/** Increase the rate at which item zones are restocked. Total time to restock = Base time to restock * (0.975 ^ RestockRateUpgrade).*/
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category="Ugprades")
	int ItemZoneRestockRate{0};	
};
