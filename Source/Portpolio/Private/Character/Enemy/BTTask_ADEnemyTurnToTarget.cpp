// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/Character/Enemy/BTTask_ADEnemyTurnToTarget.h"
#include "../Public/Character/Enemy/ADAIController.h"
#include "../Public/Character/Enemy/ADEnemyCharacter.h"
#include "../Public/Character/Player/PlayerCharacter.h"

#include "BehaviorTree/BlackboardComponent.h"

UBTTask_ADEnemyTurnToTarget::UBTTask_ADEnemyTurnToTarget()
{
	NodeName = TEXT("ADEnemyTurn");
}

EBTNodeResult::Type UBTTask_ADEnemyTurnToTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	auto Character = Cast<AADEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());

	if (Character == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : ADEnemyCharacter"));
		return EBTNodeResult::Failed;
	}

	auto Target = Cast<APlayerCharacter>(OwnerComp.GetBlackboardComponent()->GetValueAsObject(AADAIController::targetKey_));

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