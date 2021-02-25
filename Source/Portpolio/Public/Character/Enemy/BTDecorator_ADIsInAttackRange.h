// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSetting/Portpolio.h"

#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_ADIsInAttackRange.generated.h"

/**
 * 
 */
UCLASS()
class PORTPOLIO_API UBTDecorator_ADIsInAttackRange : public UBTDecorator
{
	GENERATED_BODY()

public:
	UBTDecorator_ADIsInAttackRange();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

private:
};
