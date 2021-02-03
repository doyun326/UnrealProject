// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSetting/Portpolio.h"

#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_MinionTurnToTarget.generated.h"

/**
 * 
 */
UCLASS()
class PORTPOLIO_API UBTTask_MinionTurnToTarget : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_MinionTurnToTarget();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:
};
