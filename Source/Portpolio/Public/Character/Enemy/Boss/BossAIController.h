// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSetting/Portpolio.h"

#include "AIController.h"
#include "BossAIController.generated.h"

/**
 * 
 */
UCLASS()
class PORTPOLIO_API ABossAIController : public AAIController
{
	GENERATED_BODY()

public:
	ABossAIController();

	virtual void OnPossess(APawn* InPawn) override;

	static const FName	homePosKey_;
	static const FName	patrolPosKey_;
	static const FName	targetKey_;
	
private:
	UPROPERTY()
		class UBehaviorTree*			bossBT_;
	UPROPERTY()
		class UBlackboardData*			bossBB_;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		class UBehaviorTreeComponent*	behaviorTree_;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		class UBehaviorTree*			bTree_;

	class UBlackboardComponent* blackboard_;
	class UAISenseConfig_Sight* sightConfig_;
};
