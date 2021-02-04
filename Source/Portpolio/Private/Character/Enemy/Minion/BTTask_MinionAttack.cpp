// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Character/Enemy/Minion/BTTask_MinionAttack.h"
#include "../Public/Character/Enemy/Minion/MinionAIController.h"
#include "../Public/Character/Enemy/Minion/EnemyMinionCharacter.h"

#define ATTACKRANGE_MIN		1
#define ATTACKRANGE_MAX		3

UBTTask_MinionAttack::UBTTask_MinionAttack()
{
	bNotifyTick = true;

	isAttacking_ = false;
}

EBTNodeResult::Type UBTTask_MinionAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Character = Cast<AEnemyMinionCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	int32 RandNum = FMath::RandRange(ATTACKRANGE_MIN, ATTACKRANGE_MAX);

	if (Character == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : AEnemyMinionCharacter"));
		return EBTNodeResult::Failed;
	}

	ABLOG(Warning, TEXT("%d"), RandNum);
	
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

void UBTTask_MinionAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	if (!isAttacking_)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
