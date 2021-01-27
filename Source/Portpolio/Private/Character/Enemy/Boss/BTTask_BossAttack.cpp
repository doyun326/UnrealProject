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
		Character->FirstAttack();
		break;
	case ATTACK_TWO:
		Character->SecondAttack();
		break;
	case ATTACK_THREE:
		Character->ThirdAttack();
		break;
	}

	//Character->Attack();
	isAttacking_ = true;

	Character->OnAttackFirEnd.AddLambda([this]()-> void
		{
			isAttacking_ = false;
		});
	Character->OnAttackSecEnd.AddLambda([this]()-> void
		{
			isAttacking_ = false;
		});
	Character->OnAttackThiEnd.AddLambda([this]()-> void
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
