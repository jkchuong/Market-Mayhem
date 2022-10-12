// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.generated.h"

UENUM()
enum class ItemEnum : uint8
{
  Detergent    UMETA(DisplayName = "Detergent"),
  Cake         UMETA(DisplayName = "Cake"),
  Coffee       UMETA(DisplayName = "Coffee"),
  Pizza		   UMETA(DisplayName = "Pizza"),


  COUNT_MAX_ITEMS,
};


UCLASS()
class MAYHEMMARKET_API AItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItem();
	AItem(ItemEnum itemEnum);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditDefaultsOnly, Category="Components")
	UStaticMeshComponent* ItemMesh;

public:

	UPROPERTY(EditAnywhere, Category="Item")
	ItemEnum ItemType{ItemEnum::Detergent};

	UPROPERTY(VisibleInstanceOnly)
	FString ItemName{};

	/**
	 * The size of the item to be added to the shopping cart.
	*/
	UPROPERTY(EditDefaultsOnly, Category="Item")
	float ItemSize{5};

	/**
	 * The amount of points this item has, to be calculated as the final score.
	*/
	UPROPERTY(EditDefaultsOnly, Category="Item")
	int ItemPoints{10};

};