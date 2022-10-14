// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShopperAIController.generated.h"

/**
 * 
 */
UCLASS()
class MAYHEMMARKET_API AShopperAIController : public AAIController
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

private:

	/** How close to the item zone they should get. */
	UPROPERTY(EditAnywhere, Category="Movement")
	float AcceptanceRadius{100};

	UPROPERTY(EditAnywhere)
	UBehaviorTree* AIBehavior;

	UBlackboardComponent* BlackboardComponent;
	
};
