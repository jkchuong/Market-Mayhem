// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShopperCharacter.generated.h"

class AItem;

UCLASS()
class MAYHEMMARKET_API AShopperCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShopperCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

	/** For displaying what needs to be purchased */
	UPROPERTY(EditAnywhere, Category="Shopping")
	TMap<FString, int> ShoppingList{};

	/** For colliding with trigger zone of item and purchase zones.*/
	UCapsuleComponent* CapsuleComponent;
	FTimerHandle TransferRateTimerHandle;

	/** The mesh for the shopping trolley. Will do the generate overlap events*/
	UPROPERTY(EditAnywhere, Category="Shopping")
	UStaticMeshComponent* ShoppingCartMesh;

	/** The number of items the player takes per second.*/
	UPROPERTY(EditAnywhere, Category="Shopping")
	float BaseTakeItemRate{8.0f};

	/** The number of items the player purchases per second.*/
	UPROPERTY(EditAnywhere, Category="Shopping")
	float BasePurchaseItemRate{9.0f};

	/** The number of items the player takes per second.*/
	UPROPERTY(VisibleAnywhere, Category="Shopping")
	float TakeItemRate{8.0f};

	/** The number of items the player purchases per second.*/
	UPROPERTY(VisibleAnywhere, Category="Shopping")
	float PurchaseItemRate{9.0f};

	/** The scaling of the shopping lists. This number adds to the total number of times a new item is generated for a single shopping list.
	 *  It also multiplies the random range the shopping list could request.
	 *  E.g a value of 10 would change the number of items it could request from 5 - 20 to 50 - 100.
	*/
	UPROPERTY(EditAnywhere, Category="Shopping")
	float ShoppingListDifficulty{1.0f};

	/** The score of the player. For each shopping list a player completes, 100 score is added.
	 *  The final score will be multiplied by score multiplier upgrades.
	*/
	UPROPERTY(EditAnywhere, Category="Shopping")
	float Score{0.0f};

	/** The Multiplier of the score that can be increased with upgrades.*/
	UPROPERTY(EditAnywhere, Category="Shopping")
	float ScoreMultiplier{0};

	UPROPERTY(VisibleAnywhere, Category="Shopping")
	float MovementSpeed{0};

	/** Time until the round ends. i.e 120 means that this level will last for 2 minutes (shop is open for 120 seconds)*/
	UPROPERTY(EditAnywhere, Category="Shopping")
	float ShopDuration{60.0f};
	FTimerHandle ShopDurationTimerHandle;

	/** For Spawning smoke trailes behind the cart*/
	UPROPERTY(EditAnywhere, Category="Movement")
	UParticleSystemComponent* TrailParticles;

	UPROPERTY(EditAnywhere, Category="Shopping")
	USoundBase* ItemSound;

	/** FUNCTIONS */

	UFUNCTION()
	void OnPlayerEnterItemZone(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult);

	UFUNCTION()
	void OnPlayerExitZone(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 otherBodyIndex);

	UFUNCTION()
	void AddItemToShoppingCart(AItemZone* ItemZone);

	UFUNCTION()
	void RemoveItemFromShoppingCart();

	UFUNCTION()
	void GenerateShoppingList();

	/** Close the shop - ends the round and calls game mode base to deal with it. */
	UFUNCTION()
	void CloseShop();

	FString GetStringFromMap(const TMap<FString, int>& Map) const;

public:

	/** For taking away player controls before the round begins.*/
	UPROPERTY(EditAnywhere, Category="Shopping", BlueprintReadWrite)
	bool bCanMove{true};

	UPROPERTY(EditAnywhere, Category="Shopping", BlueprintReadWrite)
	class UShoppingCart* ShoppingCart;

	UFUNCTION(BlueprintPure)
	FString GetShoppingListAsFString() const;

	UFUNCTION(BlueprintPure)
	FString GetShoppingCartAsFString() const;

	UFUNCTION(BlueprintPure)
	float GetShoppingCartCapacity() const;

	UFUNCTION(BlueprintPure)
	FTimerHandle GetShopDurationTimerHandle() const;

	UFUNCTION(BlueprintPure)
	float GetPlayerScore() const;

	UFUNCTION(BlueprintCallable)
	void OpenShop();

	UFUNCTION(BlueprintCallable)
	void SetPlayerFinalStats(class UUpgradesSaveGame* SavedGame);

	TMap<FString, int> GetShoppingList() const;
	bool IsShopOpen() const;
};
