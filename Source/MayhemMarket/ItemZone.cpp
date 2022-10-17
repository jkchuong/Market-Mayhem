// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemZone.h"

#include "Item.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"

// Sets default values
AItemZone::AItemZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerZone = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Zone"));
	TriggerZone->SetGenerateOverlapEvents(true);
	TriggerZone->SetBoxExtent(FVector(120.0f, 220.0f, 100.0f));
	SetRootComponent(TriggerZone);

	StorageMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Storage Mesh"));
	StorageMesh->SetupAttachment(RootComponent);

	// For the default position of item to display. This will let the player know what item is being sold at this position
	ItemDisplayPosition = CreateDefaultSubobject<USceneComponent>(TEXT("Item Display Position"));
	ItemDisplayPosition->SetupAttachment(RootComponent);
	ItemDisplayPosition->SetRelativeLocation(FVector(0.0f, 0.0f, 235.0f));
	ItemDisplayPosition->SetRelativeRotation(FRotator(-30.0f, 0.0f, 0.0f));

	// Spawn UI to display the number of items left that could be purchased and time to restock
	ItemCount = CreateDefaultSubobject<UWidgetComponent>(TEXT("Item Count Widget"));
	ItemCount->SetupAttachment(RootComponent);
	ItemCount->SetRelativeLocation(FVector(0.0f, 0.0f, 180.0f));

	Restock();
}

// Called when the game starts or when spawned
void AItemZone::BeginPlay()
{
	Super::BeginPlay();

	// Spawn the display to represent the item that can be purchased at this zone
	if (ItemClass)
	{
		Item = GetWorld()->SpawnActor<AItem>(ItemClass);
		Item->AttachToComponent(ItemDisplayPosition, FAttachmentTransformRules::KeepRelativeTransform, TEXT("Item Display"));
		Item->SetActorScale3D(FVector::OneVector * 3);
		Item->SetOwner(this);
	}
}

// Called every frame
void AItemZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemZone::Restock()
{
	Stock = MaximumStock;
}

AItem* AItemZone::GetItem() const
{
	return Item;
}

bool AItemZone::GetStockValid() const
{
	return Stock > 0;
}

void AItemZone::TakeItem()
{
	Stock--;

	// Restock with timer if stock runs out
	if (!GetStockValid())
	{
		GetWorldTimerManager().SetTimer(RestockTimerHandle, this, &AItemZone::Restock, TimeToRestock, false);
	} 
}

float AItemZone::GetStockPercentageRemaining() const
{
	return (Stock / static_cast<float>(MaximumStock));
}

FTimerHandle AItemZone::GetRestockTimerHandle() const
{
	return RestockTimerHandle;
}