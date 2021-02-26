// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Character/Enemy/BTService_IsADEnemyHit.h"
#include "../Public/Character/Enemy/ADAIController.h"
#include "../Public/Character/Enemy/ADEnemyCharacter.h"
#include "../Public/Character/Player/PlayerCharacter.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

UBTService_IsADEnemyHit::UBTService_IsADEnemyHit()
{
	NodeName = TEXT("ADEnemyIsHitService");
}

void UBTService_IsADEnemyHit::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	auto myCharacter = Cast<AADEnemyCharacter>(OwnerComp.GetAIOwner()->GetPawn());
	UWorld* World = myCharacter->GetWorld();

	if (myCharacter == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : myCharacter_"));
		return;
	}

	if (World == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : World"));
		return;
	}

	bool bResult = myCharacter->GetIsHiting();

	if (bResult)
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AADAIController::isHitKey_, true);
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AADAIController::isHitKey_, false);
	}
}