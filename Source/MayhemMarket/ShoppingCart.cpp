// Fill out your copyright notice in the Description page of Project Settings.


#include "ShoppingCart.h"

#include "Item.h"

// Sets default values for this component's properties
UShoppingCart::UShoppingCart()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UShoppingCart::BeginPlay()
{
	Super::BeginPlay();

}


// Called every frame
void UShoppingCart::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UShoppingCart::AddItem(FString ItemToAdd)
{
	// Only add an item if there is capacity
	if (UsedCapacity >= MaximumCapacity)
	{
		return false;
	}

	// If shopping cart already contains the item then add it, else make a new item
	if (Storage.Contains(ItemToAdd))
	{
		Storage[ItemToAdd]++;
	}
	else
	{
		Storage.Emplace(ItemToAdd, 1);
	}

	UsedCapacity++;

	return true;
}

bool UShoppingCart::RemoveItem(FString ItemToRemove)
{
	UE_LOG(LogTemp, Warning, TEXT("Removing Item with name %s"), *ItemToRemove);

	if (!Storage.Contains(ItemToRemove) || Storage[ItemToRemove] <= 0)
	{
		return false;
	}

	Storage[ItemToRemove]--;
	UsedCapacity--;

	return true;
}