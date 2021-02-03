// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Character/Enemy/Minion/BTTask_MinionTurnToTarget.h"
#include "../Public/Character/Enemy/Minion/MinionAIController.h"
#include "../Public/Character/Enemy/Minion/EnemyMinionCharacter.h"
#include "../Public/Character/Player/PlayerCharacter.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTTask_MinionTurnToTarget::UBTTask_MinionTurnToTarget()
{
	NodeName = TEXT("MinonTurn");
}

EBTNodeResult::Type UBTTask_MinionTurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Character = Cast<AEnemyMinionCharacter>(OwnerComp.GetAIOwner()->GetPawn());

	if (Character == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : MinionCharacter"));
		return EBTNodeResult::Failed;
	}

	auto Target = Cast<APlayerCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AMinionAIController::targetKey_));

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
