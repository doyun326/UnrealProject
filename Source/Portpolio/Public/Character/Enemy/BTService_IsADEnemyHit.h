// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSetting/Portpolio.h"

#include "BehaviorTree/BTService.h"
#include "BTService_IsADEnemyHit.generated.h"

/**
 * 
 */
UCLASS()
class PORTPOLIO_API UBTService_IsADEnemyHit : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_IsADEnemyHit();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
private:
};
