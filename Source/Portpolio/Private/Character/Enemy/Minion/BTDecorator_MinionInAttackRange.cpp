// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Character/Enemy/Minion/BTDecorator_MinionInAttackRange.h"
#include "../Public/Character/Enemy/Minion/MinionAIController.h"
#include "../Public/Character/Player/PlayerCharacter.h"
#include "../Public/Character/Enemy/Minion/EnemyMinionCharacter.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

#define ATTACK_RANGE 300.0f

UBTDecorator_MinionInAttackRange::UBTDecorator_MinionInAttackRange()
{
	NodeName = TEXT("MinionCanAttack");
}

bool UBTDecorator_MinionInAttackRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool bResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	auto ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	UWorld* World = ControllingPawn->GetWorld();

	if (ControllingPawn == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : ControllingPawn"));
		return false;
	}

	if (World == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : World"));
		return false;
	}

	FVector Center = ControllingPawn->GetActorLocation();
	auto Target = Cast<APlayerCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AMinionAIController::targetKey_));

	if (Target == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : Target"));
		return false;
	}

	bResult = (Target->GetDistanceTo(ControllingPawn) <= ATTACK_RANGE);

#ifdef DRAW_DEBUGHELPER
	{
		if (bResult)
		{
			DrawDebugSphere(World, Center, ATTACK_RANGE, 16, FColor::Green, false, 0.2f);
		}
		else
		{
			DrawDebugSphere(World, Center, ATTACK_RANGE, 16, FColor::Red, false, 0.2f);
		}
	}
#endif

	return bResult;
}