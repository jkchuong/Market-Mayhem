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

bool UShoppingCart::AddItem(AItem* ItemToAdd)
{
	// Only add an item if there is capacity
	if (ItemToAdd->ItemSize + UsedCapacity > MaximumCapacity)
	{
		return false;
	}

	// If shopping cart already contains the item then add it, else make a new item
	FString ItemName = ItemToAdd->ItemName;
	if (StorageMap.Contains(ItemName))
	{
		StorageMap[ItemName]++;
	}
	else
	{
		StorageMap.Emplace(ItemName, 1);
	}

	UsedCapacity += ItemToAdd->ItemSize;

	// TODO: Spawn item in shopping cart 

	return true;
}

bool UShoppingCart::RemoveItem(AItem* ItemToRemove)
{
	FString ItemName = ItemToRemove->ItemName;
	if (!StorageMap.Contains(ItemName))
	{
		return false;
	}

	StorageMap[ItemName]--;
	UsedCapacity -= ItemToRemove->ItemSize;

	return true;
}