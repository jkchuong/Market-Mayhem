// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopperCharacter.h"

#include "ShoppingCart.h"
#include "ItemZone.h"
#include "PurchaseZone.h"
#include "Components/CapsuleComponent.h"
#include "Item.h"
#include "MayhemMarketGameModeBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "UpgradesSaveGame.h"
#include "Particles/ParticleSystemComponent.h"


// Sets default values
AShopperCharacter::AShopperCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ShoppingCart = CreateDefaultSubobject<UShoppingCart>(TEXT("Shopping Cart"));
	AddOwnedComponent(ShoppingCart);
	
	CapsuleComponent = GetCapsuleComponent();
	
	ShoppingCartMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Shopping Cart Mesh"));
	ShoppingCartMesh->SetupAttachment(RootComponent);

	TrailParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Trail Particles"));
	TrailParticles->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AShopperCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	CapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &AShopperCharacter::OnPlayerEnterItemZone);
	CapsuleComponent->OnComponentEndOverlap.AddDynamic(this,&AShopperCharacter::OnPlayerExitZone);

	// Get random skins each time the level is loaded
	if (!Skins.IsEmpty())
	{	
		int RandomSkin = FMath::RandRange(0, Skins.Num() - 1);
		GetMesh()->SetSkeletalMesh(Skins[RandomSkin]);
	}

	// For using the camera to rotate the player, but allow AI to rotate smoothly
	if (IsPlayerControlled())
	{
		bUseControllerRotationYaw = true;
		GetCharacterMovement()->bOrientRotationToMovement = false;
	}

	// Initialise empty shopping list so we don't need to loop to check if it contains something every time we generate a random shopping list
	for (int Item{0}; Item != static_cast<int>(ItemEnum::COUNT_MAX_ITEMS); Item++)
	{
		ItemEnum ItemAsEnum = static_cast<ItemEnum>(Item);
		FString ItemAsFString = UEnum::GetValueAsString(ItemAsEnum);
		ShoppingList.Emplace(ItemAsFString, 0);
	}

	// Generate initial shopping list here to begin the game
	GenerateShoppingList();

}

// Called every frame
void AShopperCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
	if (GetVelocity().Length() > 0)
	{
		TrailParticles->Activate();
	}
	else
	{
		TrailParticles->Deactivate();
	}

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
	if (!bCanMove) return;
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AShopperCharacter::MoveRight(float AxisValue)
{
	if (!bCanMove) return;
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AShopperCharacter::OnPlayerEnterItemZone(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 otherBodyIndex, bool bFromSweep, const FHitResult& sweepResult)
{
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

		GetWorldTimerManager().SetTimer(TransferRateTimerHandle, TransferEnableTimerDelegate, 1/TakeItemRate, true);
	}

	// Case for entering PurchaseZone
	APurchaseZone* PurchaseZone = Cast<APurchaseZone>(OtherActor);
	if (PurchaseZone)
	{
		// Start timer that starts removing things from the player
		GetWorldTimerManager().SetTimer(TransferRateTimerHandle, this, &AShopperCharacter::RemoveItemFromShoppingCart, 1/PurchaseItemRate, true);
	}
}

void AShopperCharacter::OnPlayerExitZone(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 otherBodyIndex)
{
	GetWorldTimerManager().ClearTimer(TransferRateTimerHandle);
}

void AShopperCharacter::AddItemToShoppingCart(AItemZone* ItemZone)
{
	// Only add the item to shopping cart if there is stock and shopping cart has capacity
	if (ItemZone->GetStockValid())
	{
		if (ShoppingCart->AddItem(ItemZone->GetItem()->ItemName))
		{
			if (ItemSound)
			{
				UGameplayStatics::PlaySoundAtLocation(this, ItemSound, GetActorLocation());
			}
			ItemZone->TakeItem();
		}
	}
}

void AShopperCharacter::RemoveItemFromShoppingCart()
{
	bool bShoppingListEmpty{true};
	for (TPair<FString, int>& ShoppingListItem : ShoppingList)
	{
		// Return once an item is removed and wait for the next call from the FTimerHandle
		// We don't want to loop through all at the same time or it'll remove all valid items instantly 
		// We want to remove items at a controlled rate
		if (ShoppingListItem.Value > 0)
		{
			bShoppingListEmpty = false;

			if (ShoppingCart->RemoveItem(ShoppingListItem.Key))
			{
				Score += ScoreMultiplier;
				ShoppingListItem.Value--;
				return;
			}
		}
	}

	if (bShoppingListEmpty)
	{
		// If we reach here, that means shipping list item value <= 0 for all items so we need to generate new list
		GenerateShoppingList();
	}


}

void AShopperCharacter::GenerateShoppingList()
{
	int TotalPossibleItems = static_cast<int>(ItemEnum::COUNT_MAX_ITEMS);
	int NumberOfTimesToSelect = 1 + FMath::CeilToInt(ShoppingListDifficulty / 3);

	for (int i{0}; i < NumberOfTimesToSelect; i++)
	{
		ItemEnum ItemSelected = static_cast<ItemEnum>(FMath::RandRange(0, TotalPossibleItems - 1));
		int NumberOfItemRequired = FMath::RandRange(5 * ShoppingListDifficulty, 20 * ShoppingListDifficulty);
		FString ItemSelectedAsFString = UEnum::GetValueAsString(ItemSelected);

		if (!ShoppingList.Contains(ItemSelectedAsFString))
		{
			ShoppingList.Emplace(ItemSelectedAsFString, NumberOfItemRequired);
		}
		else
		{
			ShoppingList[ItemSelectedAsFString] += NumberOfItemRequired;
		}

	}
}

void AShopperCharacter::CloseShop()
{
	AMayhemMarketGameModeBase* GameModeBase = GetWorld()->GetAuthGameMode<AMayhemMarketGameModeBase>();

	if (GameModeBase)
	{
		GameModeBase->EndGame(Score);
	}

	DetachFromControllerPendingDestroy();
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

FTimerHandle AShopperCharacter::GetShopDurationTimerHandle() const
{
	return ShopDurationTimerHandle;
}

float AShopperCharacter::GetPlayerScore() const
{
	return Score;
}

void AShopperCharacter::OpenShop()
{
	GetMesh()->WakeAllRigidBodies();

	if (IsPlayerControlled())
	{
		GetWorldTimerManager().SetTimer(ShopDurationTimerHandle, this, &AShopperCharacter::CloseShop, ShopDuration);
	}
}

TMap<FString, int> AShopperCharacter::GetShoppingList() const
{
	return ShoppingList;
}

bool AShopperCharacter::IsShopOpen() const
{
	return ShopDurationTimerHandle.IsValid();
}

void AShopperCharacter::SetPlayerFinalStats(UUpgradesSaveGame* SavedGame)
{
	// Load upgrades from Save Data here. This will give us persistent stats between level changes.
	// Synchronous loading used as there isn't much data to load. Use asynchronous loading if it expands.
	if (SavedGame)
	{	
		UE_LOG(LogTemp, Warning, TEXT("Saved game found in shopper character witih score multiplier: %d"), SavedGame->ScoreMultiplier);
		UE_LOG(LogTemp, Warning, TEXT("Saved game found in shopper character witih points: %d"), SavedGame->Points);

		ScoreMultiplier = 100 * FMath::Pow(1.02, SavedGame->ScoreMultiplier);
		MovementSpeed = FMath::Pow(1.1, SavedGame->Movement);
		GetCharacterMovement()->MaxWalkSpeed = 600 * MovementSpeed;
		ShoppingCart->MaximumCapacity = ShoppingCart->BaseCapacity + (10 * SavedGame->CartCapacity);
		TakeItemRate = BaseTakeItemRate + (1.5 * SavedGame->TakeItemRate);
		PurchaseItemRate = BasePurchaseItemRate + (1.5 * SavedGame->PurchaseItemRate);
	}
}


