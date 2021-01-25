// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSetting/Portpolio.h"

#include "BehaviorTree/BTService.h"
#include "BTBossService_Detect.generated.h"

/**
 * 
 */
UCLASS()
class PORTPOLIO_API UBTBossService_Detect : public UBTService
{
	GENERATED_BODY()

public:
	UBTBossService_Detect();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
private:
};
