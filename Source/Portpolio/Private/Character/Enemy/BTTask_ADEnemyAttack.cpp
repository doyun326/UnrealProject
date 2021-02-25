// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Character/Enemy/BTTask_ADEnemyAttack.h"
#include "../Public/Character/Enemy/ADEnemyCharacter.h"
#include "../Public/Character/Enemy/ADAIController.h"


#define ATTACKRANGE_MIN		1
#define ATTACKRANGE_MAX		2

UBTTask_ADEnemyAttack::UBTTask_ADEnemyAttack()
{
	bNotifyTick = true;

	isAttacking_ = false;
}

EBTNodeResult::Type UBTTask_ADEnemyAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Character = Cast<AADEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	int32 RandNum = FMath::RandRange(ATTACKRANGE_MIN, ATTACKRANGE_MAX);

	if (Character == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : ADEnemyCharacter"));
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

	return EBTNodeResult::InProgress;
}

void UBTTask_ADEnemyAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (!isAttacking_)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}