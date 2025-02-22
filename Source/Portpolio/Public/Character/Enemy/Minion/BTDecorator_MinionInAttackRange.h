// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSetting/Portpolio.h"

#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_MinionInAttackRange.generated.h"

/**
 * 
 */
UCLASS()
class PORTPOLIO_API UBTDecorator_MinionInAttackRange : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UBTDecorator_MinionInAttackRange();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
