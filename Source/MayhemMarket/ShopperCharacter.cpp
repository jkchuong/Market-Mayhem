// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopperCharacter.h"

#include "ShoppingCart.h"

// Sets default values
AShopperCharacter::AShopperCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ShoppingCart = CreateDefaultSubobject<UShoppingCart>(TEXT("Shopping Cart"));
	AddOwnedComponent(ShoppingCart);
	
}

// Called when the game starts or when spawned
void AShopperCharacter::BeginPlay()
{
	Super::BeginPlay();
	
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