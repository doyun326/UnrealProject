// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Character/Enemy/Minion/BTService_IsMinionHit.h"
#include "../Public/Character/Enemy/Minion/MinionAIController.h"
#include "../Public/Character/Enemy/Minion/EnemyMinionCharacter.h"
#include "../Public/Character/Player/PlayerCharacter.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

UBTService_IsMinionHit::UBTService_IsMinionHit()
{
	NodeName = TEXT("MinionIsHitService");
}

void UBTService_IsMinionHit::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	auto myCharacter = Cast<AEnemyMinionCharacter>(OwnerComp.GetAIOwner()->GetPawn());
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
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMinionAIController::isHitKey_, true);
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsBool(AMinionAIController::isHitKey_, false);
	}
}