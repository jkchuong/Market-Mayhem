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


private:

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> HUDScreenClass;

	UPROPERTY()
	UUserWidget* HUDScreen;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> EndScreenClass;
	
	UPROPERTY()
	UUserWidget* EndScreen;
};
