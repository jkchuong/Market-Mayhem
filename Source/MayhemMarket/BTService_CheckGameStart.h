// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_CheckGameStart.generated.h"

/**
 * 
 */
UCLASS()
class MAYHEMMARKET_API UBTService_CheckGameStart : public UBTService_BlackboardBase
{
	GENERATED_BODY()

public:

	UBTService_CheckGameStart();

protected:

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

	
};
