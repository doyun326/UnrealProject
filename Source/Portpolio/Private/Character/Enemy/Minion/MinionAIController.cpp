// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Character/Enemy/Minion/MinionAIController.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

#define MINIONBB_PATH	"/Game/My/AI/Minion/MinionAI_BB.MinionAI_BB"
#define MINIONBT_PATH	"/Game/My/AI/Minion/MinionAI_BT.MinionAI_BT"

const FName AMinionAIController::homePosKey_(TEXT("HomePos"));
const FName AMinionAIController::patrolPosKey_(TEXT("PatrolPos"));
const FName AMinionAIController::targetKey_(TEXT("Target"));
const FName AMinionAIController::isHitKey_(TEXT("isHit"));

AMinionAIController::AMinionAIController()
{
	//BlackBoard
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT(MINIONBB_PATH));

	if (BBObject.Succeeded())
	{
		ABLOG(Warning, TEXT("Success : BBObject"));
		minionBB_ = BBObject.Object;
	}

	//Behavior Tree
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT(MINIONBT_PATH));

	if (BTObject.Succeeded())
	{
		ABLOG(Warning, TEXT("Success : BTObject"));
		minionBT_ = BTObject.Object;
	}
}

void AMinionAIController::BeginPlay()
{
	Super::BeginPlay();

}

void AMinionAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (UseBlackboard(minionBB_, Blackboard))
	{
		Blackboard->SetValueAsVector(homePosKey_, InPawn->GetActorLocation());
		if (!RunBehaviorTree(minionBT_))
		{
			ABLOG(Warning, TEXT("BossAIController couldn't BehaviorTree!"));
		}
	}
}