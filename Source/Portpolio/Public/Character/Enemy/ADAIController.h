// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSetting/Portpolio.h"

#include "AIController.h"
#include "ADAIController.generated.h"

/**
 * 
 */
UCLASS()
class PORTPOLIO_API AADAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AADAIController();

	virtual void PostInitializeComponents() override;
	virtual void OnPossess(APawn* InPawn) override;

	void	StopAI();
	void	EnemyKill(class AADEnemyCharacter* _killedNpc) const;
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
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		class UBehaviorTree*			assetBT_;
	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, Category = "AI", meta = (AllowPrivateAccess = "true"))
		class UBlackboardData*			assetBB_;

	class UBlackboardComponent*		blackboard_;
	class UAISenseConfig_Sight*		sightConfig_;

	bool	isHit_;
};
