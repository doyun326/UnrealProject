// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Character/Enemy/Boss/BTTask_BossAttack.h"
#include "../Public/Character/Enemy/Boss/BossAIController.h"
#include "../Public/Character/Enemy/Boss/BossCharacter.h"

#define ATTACKRANGE_MIN		1
#define ATTACKRANGE_MAX		3

UBTTask_BossAttack::UBTTask_BossAttack()
{
	bNotifyTick = true;

	isAttacking_ = false;
}

EBTNodeResult::Type UBTTask_BossAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Character = Cast<ABossCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	int32 RandNum = FMath::RandRange(ATTACKRANGE_MIN, ATTACKRANGE_MAX);

	if (Character == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : BossCharacter"));
		return EBTNodeResult::Failed;
	}

	switch (RandNum)
	{
	case ATTACK_ONE:
		Character->onFirstAttack_.Broadcast(true);
		break;
	case ATTACK_TWO:
		Character->onSecondAttack_.Broadcast(true);
		break;
	case ATTACK_THREE:
		Character->onThirdAttack_.Broadcast(true);
		break;
	}

	isAttacking_ = true;

	Character->onFirstAttack_.AddLambda([this](bool _isAttack)-> void
		{
			if (!_isAttack)
			{
				isAttacking_ = false;
			}
		});
	Character->onSecondAttack_.AddLambda([this](bool _isAttack)-> void
		{
			if (!_isAttack)
			{
				isAttacking_ = false;
			}
		});
	Character->onThirdAttack_.AddLambda([this](bool _isAttack)-> void
		{
			if (!_isAttack)
			{
				isAttacking_ = false;
			}
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
