// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Character/Enemy/Boss/BTTask_BossAttack.h"
#include "../Public/Character/Enemy/Boss/BossAIController.h"
#include "../Public/Character/Enemy/Boss/BossCharacter.h"

UBTTask_BossAttack::UBTTask_BossAttack()
{
	bNotifyTick = true;

	isAttacking_ = false;
}

EBTNodeResult::Type UBTTask_BossAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Character = Cast<ABossCharacter>(OwnerComp.GetAIOwner()->GetPawn());

	if (Character == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : BossCharacter"));
		return EBTNodeResult::Failed;
	}

	Character->Attack();
	isAttacking_ = true;
	Character->OnAttackEnd.AddLambda([this]()-> void
		{
			isAttacking_ = false;
		});

	return EBTNodeResult::InProgress;
}

void UBTTask_BossAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (!isAttacking_)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
