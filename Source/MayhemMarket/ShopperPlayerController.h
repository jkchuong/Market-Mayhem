// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShopperPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class MAYHEMMARKET_API AShopperPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:

	virtual void BeginPlay() override;

public:

	AShopperPlayerController();
	
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;

	UFUNCTION(BlueprintCallable)
	void ReturnToMenu();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float PlayerScore{0.0f};

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<float> TopScores;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float TimeToBegin{3.0f};

	UPROPERTY(BlueprintReadOnly)
	FTimerHandle DelayInputTimerHandle;

	UFUNCTION(BlueprintPure)
	FString GetScoresAsFString() const;

	UFUNCTION(BlueprintCallable)
	void BeginGame();

	/** For applying the upgrades to the player on click start button before the round begins. */
	UFUNCTION(BlueprintCallable)
	void ApplySaveToPlayer(UUpgradesSaveGame* SavedGame);

	UFUNCTION(BlueprintCallable)
	void OnClickUpgrade();

	UFUNCTION(BlueprintCallable)
	void OnClickCredits();

	UFUNCTION(BlueprintCallable)
	void OnClickReturn();

	UFUNCTION(BlueprintCallable)
	void OnClickQuit();

	void ChangeScreenTo(UUserWidget* ScreenToChangeTo);

	/** From getting the level of something to the price of upgrading to the next. 
	 *  Is equal to BaseUpgradeCost * (Rate Increase ^ Level) 
	*/
	UFUNCTION(BlueprintCallable)
	int GetUpgradeCostFromLevel(int UpgradeLevel) const;

	UFUNCTION(BlueprintPure)
	bool IsUpgradeScreenDisplayed() const;

private:

	TArray<UUserWidget*> AllScreens;

	/** The base price to purchase an upgrade.*/
	UPROPERTY(EditAnywhere)
	float BaseUpgradeCost{10000.0f};

	/** The rate the prices of upgrades increase.*/
	UPROPERTY(EditAnywhere)
	float RateUpgradeIncrease{1.41f};

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> StartScreenClass;

	UPROPERTY()
	UUserWidget* StartScreen;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> HUDScreenClass;

	UPROPERTY()
	UUserWidget* HUDScreen;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> UpgradeScreenClass;

	UPROPERTY()
	UUserWidget* UpgradeScreen;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> CreditsScreenClass;

	UPROPERTY()
	UUserWidget* CreditsScreen;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> EndScreenClass;
	
	UPROPERTY()
	UUserWidget* EndScreen;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> BackgroundScreenClass;
	
	UPROPERTY()
	UUserWidget* BackgroundScreen;




};
