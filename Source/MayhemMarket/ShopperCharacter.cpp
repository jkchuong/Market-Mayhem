// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopperCharacter.h"

#include "ShoppingCart.h"
#include "ItemZone.h"
#include "PurchaseZone.h"
#include "Components/CapsuleComponent.h"
#include "Item.h"

// Sets default values
AShopperCharacter::AShopperCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ShoppingCart = CreateDefaultSubobject<UShoppingCart>(TEXT("Shopping Cart"));
	AddOwnedComponent(ShoppingCart);
	
	CapsuleComponent = GetCapsuleComponent();
}

// Called when the game starts or when spawned
void AShopperCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &AShopperCharacter::OnPlayerEnterItemZone);
	CapsuleComponent->OnComponentEndOverlap.AddDynamic(this,&AShopperCharacter::OnPlayerExitZone);

	// Generate initial shopping list here to begin the game
	GenerateShoppingList();
}

// Called every frame
void AShopperCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShopperCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShopperCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShopperCharacter::MoveRight);

	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);

}

void AShopperCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AShopperCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AShopperCharacter::OnPlayerEnterItemZone(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Player Entered %s"), *OtherComp->GetOwner()->GetActorNameOrLabel());
	// Case for entering ItemZone
	AItemZone* ItemZone = Cast<AItemZone>(OtherActor);
	if (ItemZone)
	{
		// Start timer that starts adding things to the player
		FTimerDelegate TransferEnableTimerDelegate = 
			FTimerDelegate::CreateUObject(
			this,
			&AShopperCharacter::AddItemToShoppingCart,
			ItemZone
		);

		GetWorldTimerManager().SetTimer(TransferRateTimerHandle, TransferEnableTimerDelegate, TakeItemRate, true);
	}

	// Case for entering PurchaseZone
	APurchaseZone* PurchaseZone = Cast<APurchaseZone>(OtherActor);
	if (PurchaseZone)
	{
		// Start timer that starts removing things from the player
		GetWorldTimerManager().SetTimer(TransferRateTimerHandle, this, &AShopperCharacter::RemoveItemFromShoppingCart, PurchaseItemRate, true);
	}
}

void AShopperCharacter::OnPlayerExitZone(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 otherBodyIndex)
{
	UE_LOG(LogTemp, Warning, TEXT("Player Exit %s"), *OtherComp->GetOwner()->GetActorNameOrLabel());

	GetWorldTimerManager().ClearTimer(TransferRateTimerHandle);
}

void AShopperCharacter::AddItemToShoppingCart(AItemZone* ItemZone)
{
	// Only add the item to shopping cart if there is stock and shopping cart has capacity
	if (ItemZone->GetStockValid())
	{
		if (ShoppingCart->AddItem(ItemZone->GetItem()->ItemName))
		{
			ItemZone->TakeItem();
		}
	}
}

void AShopperCharacter::RemoveItemFromShoppingCart()
{
	for (TPair<FString, int>& ShoppingListItem : ShoppingList)
	{
		if (ShoppingListItem.Value > 0 && ShoppingCart->RemoveItem(ShoppingListItem.Key))
		{
			// Return once an item is removed and wait for the next call from the FTimerHandle
			// We don't want to loop through all at the same time or it'll remove all valid items instantly 
			// We want to remove items at a controlled rate
			ShoppingListItem.Value--;
			return;
		}
	}
}

void AShopperCharacter::GenerateShoppingList()
{
	ShoppingList.Emplace(UEnum::GetValueAsString(ItemEnum::Detergent), 5);
	ShoppingList.Emplace(UEnum::GetValueAsString(ItemEnum::Pizza), 5);
}

FString AShopperCharacter::GetStringFromMap(const TMap<FString, int>& Map) const
{
	FString ReturnString;

	for (TPair<FString, int> ListItem : Map)
	{
		// Don't list the item if there's none of it left
		if (ListItem.Value <= 0)
		{
			continue;
		}

		FString NewLine;
		NewLine += ListItem.Key;
		NewLine += TEXT(" x ");
		NewLine += FString::FromInt(ListItem.Value);
		NewLine += LINE_TERMINATOR;
		NewLine.RemoveFromStart(TEXT("ItemEnum::"));

		ReturnString += NewLine;
	}

	return ReturnString;
}

FString AShopperCharacter::GetShoppingListAsFString() const
{
	return GetStringFromMap(ShoppingList);
}

FString AShopperCharacter::GetShoppingCartAsFString() const
{
	return GetStringFromMap(ShoppingCart->GetStorage());
}

float AShopperCharacter::GetShoppingCartCapacity() const
{
	return ShoppingCart->GetUsedCapacityPercentage();
}