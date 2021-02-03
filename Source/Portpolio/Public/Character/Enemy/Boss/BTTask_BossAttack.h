// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSetting/Portpolio.h"

#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_BossAttack.generated.h"

/**
 * 
 */
UCLASS()
class PORTPOLIO_API UBTTask_BossAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_BossAttack();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	virtual void TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	enum ATTACK_PATTERN
	{
		ATTACK_START,
		ATTACK_ONE,
		ATTACK_TWO,
		ATTACK_THREE,
		ATTACK_END
	};

	bool	isAttacking_;

};
