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

	// For displaying what needs to be purchased
	UPROPERTY(EditAnywhere, Category="Shopping")
	TMap<FString, int> ShoppingList{};

	// For colliding with trigger zone of item and purchase zones.
	UCapsuleComponent* CapsuleComponent;
	FTimerHandle TransferRateTimerHandle;

	UPROPERTY(EditAnywhere, Category="Shopping")
	float TakeItemRate{2.0f};

	UPROPERTY(EditAnywhere, Category="Shopping")
	float PurchaseItemRate{1.0f};

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

	FString GetStringFromMap(const TMap<FString, int>& Map) const;

public:

	UPROPERTY(EditAnywhere, Category="Shopping", BlueprintReadWrite)
	class UShoppingCart* ShoppingCart;

	UFUNCTION(BlueprintPure)
	FString GetShoppingListAsFString() const;

	UFUNCTION(BlueprintPure)
	FString GetShoppingCartAsFString() const;

	UFUNCTION(BlueprintPure)
	float GetShoppingCartCapacity() const;
};
