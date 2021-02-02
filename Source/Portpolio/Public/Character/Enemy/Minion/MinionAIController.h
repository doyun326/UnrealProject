// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSetting/Portpolio.h"

#include "AIController.h"
#include "MinionAIController.generated.h"

/**
 * 
 */
UCLASS()
class PORTPOLIO_API AMinionAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AMinionAIController();

	virtual void OnPossess(APawn* InPawn) override;

	static const FName	homePosKey_;
	static const FName	patrolPosKey_;
	static const FName	targetKey_;
	static const FName	isHitKey_;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
		class UBehaviorTree* minionBT_;
	UPROPERTY()
		class UBlackboardData* minionBB_;

};
