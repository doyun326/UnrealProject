// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Character/Enemy/BTTask_ADEnemyHit.h"
#include "../Public/Character/Enemy/ADAIController.h"
#include "../Public/Character/Enemy/ADEnemyCharacter.h"
#include "../Public/Character/Player/PlayerCharacter.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

UBTTask_ADEnemyHit::UBTTask_ADEnemyHit()
{
	isHiting_ = false;
}

EBTNodeResult::Type UBTTask_ADEnemyHit::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	return EBTNodeResult::InProgress;
}

void UBTTask_ADEnemyHit::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (!isHiting_)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}