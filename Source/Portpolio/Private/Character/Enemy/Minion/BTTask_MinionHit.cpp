// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Character/Enemy/Minion/BTTask_MinionHit.h"

UBTTask_MinionHit::UBTTask_MinionHit()
{
	isHiting_ = false;
}

EBTNodeResult::Type UBTTask_MinionHit::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	return EBTNodeResult::InProgress;
}

void UBTTask_MinionHit::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (!isHiting_)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}