// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Character/Enemy/Boss/BossAIController.h"
#include "../Public/GameSetting/WarGameInstance.h"
#include "../Public/Character/Enemy/Boss/BossCharacter.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

#define BOSSBB_PATH		"/Game/My/AI/Boss/BossAI_BB.BossAI_BB"
#define BOSSBT_PATH		"/Game/My/AI/Boss/BossAI_BT.BossAI_BT"

const FName ABossAIController::homePosKey_(TEXT("HomePos"));
const FName ABossAIController::patrolPosKey_(TEXT("PatrolPos"));
const FName ABossAIController::targetKey_(TEXT("Target"));
const FName ABossAIController::isHitKey_(TEXT("isHit"));

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
		ABLOG(Warning, TEXT("Succeess : BossBeviorTree"));
		bossBT_ = BTObject.Object;
	}
}

void ABossAIController::BeginPlay()
{
	Super::BeginPlay();

	warGameInstance_ = Cast<UWarGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (warGameInstance_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : WarGameInstance"));
		return;
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
			ABLOG(Warning, TEXT("BossAIController couldn't BehaviorTree!"));
		}
	}
}

void ABossAIController::StopAI()
{
	auto BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);

	if (BehaviorTreeComponent != nullptr)
	{
		BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
	}
}

void ABossAIController::EnemyKill(class ABossCharacter* _killedNpc) const
{
	if (warGameInstance_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : warGameInstance_"));
		return;
	}
	//warGameInstance_->SetSaveExp(_killedNpc->GetExp());
}

void ABossAIController::SetIsHit(bool _isHit)
{
	isHit_ = _isHit;
}

bool ABossAIController::GetIsHit()
{
	return isHit_;
}