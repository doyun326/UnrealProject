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

	void	StopAI();
	void	EnemyKill(class ABossCharacter* _killedNpc) const;
	void	SetIsHit(bool _isHit);
	bool	GetIsHit();

	static const FName	homePosKey_;
	static const FName	patrolPosKey_;
	static const FName	targetKey_;
	static const FName	isHitKey_;
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY()
		class UWarGameInstance*			warGameInstance_;
	UPROPERTY()
		class UBehaviorTree*			bossBT_;
	UPROPERTY()
		class UBlackboardData*			bossBB_;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		class UBehaviorTreeComponent*	behaviorTree_;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		class UBehaviorTree*			bTree_;

	class UBlackboardComponent*	blackboard_;
	class UAISenseConfig_Sight* sightConfig_;

	bool	isHit_;
};
