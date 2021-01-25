// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Character/Enemy/Boss/BTBossTask_FindPatrolPos.h"

UBTBossTask_FindPatrolPos::UBTBossTask_FindPatrolPos()
{

}

EBTNodeResult::Type UBTBossTask_FindPatrolPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	return EBTNodeResult::Failed;
}