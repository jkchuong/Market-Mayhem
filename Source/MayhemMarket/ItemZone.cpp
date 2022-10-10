// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemZone.h"

// Sets default values
AItemZone::AItemZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AItemZone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

