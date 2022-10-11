// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemZone.h"

#include "Item.h"
#include "Components/BoxComponent.h"

// Sets default values
AItemZone::AItemZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerZone = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Zone"));
	SetRootComponent(TriggerZone);
	TriggerZone->SetGenerateOverlapEvents(true);

	StorageMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Storage Mesh"));
	StorageMesh->SetupAttachment(RootComponent);

	ItemDisplayPosition = CreateDefaultSubobject<USceneComponent>(TEXT("Item Display Position"));
	ItemDisplayPosition->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AItemZone::BeginPlay()
{
	Super::BeginPlay();
	
	DrawDebugBox(GetWorld(), GetActorLocation(), TriggerZone->GetUnscaledBoxExtent(), FColor::Green, true);

	// TriggerZone->OnComponentBeginOverlap.AddDynamic(this, &AItemZone::OnPlayerEnterBox);
	// TriggerZone->OnComponentEndOverlap.AddDynamic(this, &AItemZone::OnPlayerExitBox);

	// Spawn the display to represent the item that can be purchased at this zone
	Item = GetWorld()->SpawnActor<AItem>(ItemClass);
	Item->AttachToComponent(ItemDisplayPosition, FAttachmentTransformRules::KeepRelativeTransform, TEXT("Item Display"));
	Item->SetActorScale3D(FVector::OneVector * 3);
	Item->SetOwner(this);
}

// Called every frame
void AItemZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

AItem* AItemZone::GetItem() const
{
	return Item;
}














// void AItemZone::OnPlayerEnterBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
// {
// 	UShoppingCart* ShoppingCart = OtherActor->FindComponentByClass<UShoppingCart>();
// 	if (!ShoppingCart) return;

// 	// Start timer that starts adding things to the player
// 	FTimerDelegate TransferEnableTimerDelegate = 
// 		FTimerDelegate::CreateUObject(
// 		this,
// 		&AItemZone::TryAddItemToPlayer,
// 		ShoppingCart
// 	);

// 	GetWorldTimerManager().SetTimer(TransferRateTimerHandle, TransferEnableTimerDelegate, 2.0f, true);
// }

// void AItemZone::OnPlayerExitBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
// {
// 	// Stop timer that was adding things to the player

// 	// Stop adding items when a player enters the box
// 	UShoppingCart* ShoppingCart = OtherActor->FindComponentByClass<UShoppingCart>();
// 	if (!ShoppingCart) return;
// }

// void AItemZone::TryAddItemToPlayer(UShoppingCart* ShoppingCart)
// {
// 	if (Stock <= 0) return;

// 	// Remove an item from the stock if successfully added to the shopping cart
// 	if (ShoppingCart->AddItem(Item))
// 	{
// 		Stock--;
// 	}
// }