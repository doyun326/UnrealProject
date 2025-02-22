// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Character/Enemy/BTTask_FindPatrolPos.h"
#include "../Public/Character/Enemy/ADAIController.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"

UBTTask_FindPatrolPos::UBTTask_FindPatrolPos()
{
	NodeName = TEXT("FindPatrolPos");
}

EBTNodeResult::Type UBTTask_FindPatrolPos::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

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

	FVector Origin = OwnerComp.GetBlackboardComponent()->GetValueAsVector(AADAIController::homePosKey_);

	FNavLocation NextPatrol;
	FVector PawnLocation;

	if (ControllingPawn == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : COntrollingPawn"));
		return EBTNodeResult::Failed;
	}
	else
	{
		PawnLocation = ControllingPawn->GetActorLocation();

		if (NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.0f, NextPatrol))
		{
			NextPatrol.Location.Z = 0.0f;
			NextPatrol.Location.Y += PawnLocation.Y;
			NextPatrol.Location.X += PawnLocation.X;

			OwnerComp.GetBlackboardComponent()->SetValueAsVector(AADAIController::patrolPosKey_, NextPatrol.Location);
			return EBTNodeResult::Succeeded;
		}
	}

	return EBTNodeResult::Failed;
}