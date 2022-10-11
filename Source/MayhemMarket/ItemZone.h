// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ItemZone.generated.h"

class AItem;

UCLASS()
class MAYHEMMARKET_API AItemZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemZone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	// For spawning in the item display in the game to show the player what item is on the shelves
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AItem> ItemClass;

	UPROPERTY()
	AItem* Item;

	UPROPERTY(EditAnywhere)
	int Stock{20};

	// For determining where the item displayed will spawn in the world 
	UPROPERTY(EditDefaultsOnly)
	USceneComponent* ItemDisplayPosition;

	// For interacting with the player
	UPROPERTY(EditDefaultsOnly)
	class UBoxComponent* TriggerZone;

	UPROPERTY(EditDefaultsOnly)
	UStaticMeshComponent* StorageMesh;

public:

	AItem* GetItem() const;
	bool GetStockValid() const;
	void TakeItem();
};
