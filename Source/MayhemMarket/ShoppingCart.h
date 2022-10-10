// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ShoppingCart.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MAYHEMMARKET_API UShoppingCart : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UShoppingCart();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	UPROPERTY(VisibleAnywhere)
	float UsedCapacity{0};

	UPROPERTY(VisibleAnywhere)
	TMap<FString, int> StorageMap{};

	UPROPERTY(EditAnywhere)
	float MaximumCapacity{200};

public:

	UFUNCTION(BlueprintCallable)
	bool AddItem(class AItem* ItemToAdd);

	UFUNCTION(BlueprintCallable)
	bool RemoveItem(class AItem* ItemToRemove);

};
