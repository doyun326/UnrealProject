// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Character/Enemy/Minion/BTTask_MinionFindPatrolPos.h"
#include "../Public/Character/Enemy/Minion/MinionAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

UBTTask_MinionFindPatrolPos::UBTTask_MinionFindPatrolPos()
{
	NodeName = TEXT("MinionFindPatrolPos");
}

EBTNodeResult::Type UBTTask_MinionFindPatrolPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();

	if (ControllingPawn == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : Controlling Pawn"));
		return EBTNodeResult::Failed;
	}

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(ControllingPawn->GetWorld());

	if (NavSystem == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : NavSystem"));
		return EBTNodeResult::Failed;
	}

	FVector Origin = OwnerComp.GetBlackboardComponent()->GetValueAsVector(AMinionAIController::homePosKey_);

	FNavLocation NextPatrol;

	if (NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.0f, NextPatrol))
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsVector(AMinionAIController::patrolPosKey_, NextPatrol.Location);
		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}


