// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Character/Enemy/ADAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

#define BLACKBOARD_PATH "/Game/My/AI/ADEnemy_BB.ADEnemy_BB"
#define BEHAVIORTREE_PATH "/Game/My/AI/ADEnemy_BT.ADEnemy_BT"

const FName AADAIController::homePosKey_(TEXT("HomePos"));
const FName AADAIController::patrolPosKey_(TEXT("PatrolPos"));
const FName AADAIController::targetKey_(TEXT("Target"));

AADAIController::AADAIController()
{
	//BlackBoard가져오기
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT(BLACKBOARD_PATH));

	if (BBObject.Succeeded())
	{
		ABLOG(Warning, TEXT("Succeess : ADBlackBoard"));
		assetBB_ = BBObject.Object;
	}

	//BehaviorTree 가져오기
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT(BEHAVIORTREE_PATH));

	if (BTObject.Succeeded())
	{
		ABLOG(Warning, TEXT("Succeess : ADBehaviorTree"));
		assetBT_ = BTObject.Object;
	}
}

void AADAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (UseBlackboard(assetBB_, Blackboard))
	{
		Blackboard->SetValueAsVector(homePosKey_, InPawn->GetActorLocation());

		if (!RunBehaviorTree(assetBT_))
		{
			ABLOG(Warning, TEXT("AIController couldn't BehaviorTree!"));
		}
	}
}
