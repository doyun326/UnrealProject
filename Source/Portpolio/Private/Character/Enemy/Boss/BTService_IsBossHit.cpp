// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Character/Enemy/Boss/BTService_IsBossHit.h"
#include "../Public/Character/Enemy/Boss/BossAIController.h"
#include "../Public/Character/Enemy/Boss/BossCharacter.h"
#include "../Public/Character/Player/PlayerCharacter.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

UBTService_IsBossHit::UBTService_IsBossHit()
{
	NodeName = TEXT("BossIsHitService");
}

void UBTService_IsBossHit::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	auto myCharacter = Cast<ABossCharacter>(OwnerComp.GetAIOwner()->GetPawn());
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
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABossAIController::isHitKey_, true);
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(ABossAIController::isHitKey_, false);
	}
}