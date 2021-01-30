// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSetting/Portpolio.h"

#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_BossHit.generated.h"

/**
 * 
 */
UCLASS()
class PORTPOLIO_API UBTTask_BossHit : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_BossHit();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	bool	isHiting_;

};
