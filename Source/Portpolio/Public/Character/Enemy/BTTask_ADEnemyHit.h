// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSetting/Portpolio.h"

#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_ADEnemyHit.generated.h"

/**
 * 
 */
UCLASS()
class PORTPOLIO_API UBTTask_ADEnemyHit : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_ADEnemyHit();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	bool	isHiting_;
};
