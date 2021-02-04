// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSetting/Portpolio.h"

#include "BehaviorTree/BTService.h"
#include "BTService_IsMinionHit.generated.h"

/**
 * 
 */
UCLASS()
class PORTPOLIO_API UBTService_IsMinionHit : public UBTService
{
	GENERATED_BODY()
	
public:
	UBTService_IsMinionHit();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
private:

};
