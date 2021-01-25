// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Character/Enemy/Boss/BossAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

#define BOSSBB_PATH		"/Game/My/AI/Boss/BossAI_BB.BossAI_BB"
#define BOSSBT_PATH		"/Game/My/AI/Boss/BossAI_BT.BossAI_BT"

const FName ABossAIController::homePosKey_(TEXT("HomePos"));
const FName ABossAIController::patrolPosKey_(TEXT("PatrolPos"));
const FName ABossAIController::targetKey_(TEXT("Target"));

ABossAIController::ABossAIController()
{
	//BlackBoard
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT(BOSSBB_PATH));

	if (BBObject.Succeeded())
	{
		ABLOG(Warning, TEXT("Succeess : BossBlackBoard"));
		bossBB_ = BBObject.Object;
	}

	//BehaviorTree
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT(BOSSBT_PATH));

	if (BTObject.Succeeded())
	{
		ABLOG(Warning, TEXT("Succeess : BossBevior Tree"));
		bossBT_ = BTObject.Object;
	}
}

void ABossAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (UseBlackboard(bossBB_, Blackboard))
	{
		Blackboard->SetValueAsVector(homePosKey_, InPawn->GetActorLocation());

		if (!RunBehaviorTree(bossBT_))
		{
			ABLOG(Warning, TEXT("AIController couldn't BehaviorTree!"));
		}
	}
}