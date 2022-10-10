// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemZone.h"

#include "Item.h"
#include "Components/BoxComponent.h"
#include "ShoppingCart.h"

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

	TriggerZone->OnComponentBeginOverlap.AddDynamic(this, &AItemZone::OnPlayerEnterBox);
	TriggerZone->OnComponentEndOverlap.AddDynamic(this, &AItemZone::OnPlayerExitBox);

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

void AItemZone::OnPlayerEnterBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	// Start adding items when a player enters the box
	UShoppingCart* ShoppingCart = OtherActor->FindComponentByClass<UShoppingCart>();
	if (!ShoppingCart) return;
	if (Stock <= 0) return;

	ShoppingCart->AddItem(Item);
}

void AItemZone::OnPlayerExitBox(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	// Stop adding items when a player enters the box
	UShoppingCart* ShoppingCart = OtherActor->FindComponentByClass<UShoppingCart>();
	if (!ShoppingCart) return;


}