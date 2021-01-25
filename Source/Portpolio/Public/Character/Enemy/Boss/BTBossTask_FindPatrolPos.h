// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSetting/Portpolio.h"

#include "BehaviorTree/BTTaskNode.h"
#include "BTBossTask_FindPatrolPos.generated.h"

/**
 * 
 */
UCLASS()
class PORTPOLIO_API UBTBossTask_FindPatrolPos : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTBossTask_FindPatrolPos();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

private:

};
