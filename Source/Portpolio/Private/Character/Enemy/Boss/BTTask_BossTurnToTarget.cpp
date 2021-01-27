// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Character/Enemy/Boss/BTTask_BossTurnToTarget.h"
#include "../Public/Character/Enemy/Boss/BossAIController.h"
#include "../Public/Character/Enemy/Boss/BossCharacter.h"
#include "../Public/Character/Player/PlayerCharacter.h"

#include "BehaviorTree/BlackboardComponent.h"
	
UBTTask_BossTurnToTarget::UBTTask_BossTurnToTarget()
{
	NodeName = TEXT("BossTurn");
}

EBTNodeResult::Type UBTTask_BossTurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Character = Cast<ABossCharacter>(OwnerComp.GetAIOwner()->GetPawn());

	if (Character == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : BossCharacter"));
		return EBTNodeResult::Failed;
	}

	auto Target = Cast<APlayerCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(ABossAIController::targetKey_));

	if (Target == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : Target"));
		return EBTNodeResult::Failed;
	}

	FVector LookVector = Target->GetActorLocation() - Character->GetActorLocation();
	LookVector.Z = 0.0f;
	FRotator TargeteRot = FRotationMatrix::MakeFromX(LookVector).Rotator();
	Character->SetActorRotation(FMath::RInterpTo(Character->GetActorRotation(), TargeteRot, GetWorld()->GetDeltaSeconds(), 5.0f));

	return EBTNodeResult::Succeeded;
}