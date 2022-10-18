// Fill out your copyright notice in the Description page of Project Settings.


#include "TrashZone.h"

#include "Components/BoxComponent.h"


// Sets default values
ATrashZone::ATrashZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerZone = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Zone"));
	TriggerZone->SetGenerateOverlapEvents(true);
	TriggerZone->SetBoxExtent(FVector(120.0f, 220.0f, 100.0f));
	SetRootComponent(TriggerZone);
}

// Called when the game starts or when spawned
void ATrashZone::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ATrashZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
