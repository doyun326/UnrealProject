// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Character/Enemy/Boss/BTTask_BossHit.h"

UBTTask_BossHit::UBTTask_BossHit()
{
	isHiting_ = false;
}

EBTNodeResult::Type UBTTask_BossHit::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	return EBTNodeResult::InProgress;
}

void UBTTask_BossHit::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (!isHiting_)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}