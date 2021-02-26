// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Character/Enemy/ADAIController.h"
#include "../Public/GameSetting/WarGameInstance.h"
#include "../Public/Character/Enemy/ADEnemyCharacter.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

#define BLACKBOARD_PATH "/Game/My/AI/ADEnemy_BB.ADEnemy_BB"
#define BEHAVIORTREE_PATH "/Game/My/AI/ADEnemy_BT.ADEnemy_BT"

const FName AADAIController::homePosKey_(TEXT("HomePos"));
const FName AADAIController::patrolPosKey_(TEXT("PatrolPos"));
const FName AADAIController::targetKey_(TEXT("Target"));
const FName AADAIController::isHitKey_(TEXT("isHit"));

AADAIController::AADAIController()
{
	//BlackBoard가져오기
	ConstructorHelpers::FObjectFinder<UBlackboardData> BBObject(TEXT(BLACKBOARD_PATH));

	if (BBObject.Succeeded())
	{
		ABLOG(Warning, TEXT("Succeess : ADBlackBoard"));
		assetBB_ = BBObject.Object;
	}

	//BehaviorTree 가져오기
	ConstructorHelpers::FObjectFinder<UBehaviorTree> BTObject(TEXT(BEHAVIORTREE_PATH));

	if (BTObject.Succeeded())
	{
		ABLOG(Warning, TEXT("Succeess : ADBehaviorTree"));
		assetBT_ = BTObject.Object;
	}
}

void AADAIController::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	ABLOG(Warning, TEXT("Bind AIController"));
}

void AADAIController::BeginPlay()
{
	Super::BeginPlay();

	warGameInstance_ = Cast<UWarGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (warGameInstance_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : warGameInstance"));
		return;
	}
}

void AADAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (assetBB_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : assetBB"));
	}

	if (UseBlackboard(assetBB_, Blackboard))
	{
		Blackboard->SetValueAsVector(homePosKey_, InPawn->GetActorLocation());

		if (!RunBehaviorTree(assetBT_))
		{
			ABLOG(Warning, TEXT("AIController couldn't BehaviorTree!"));
		}
	}
}

void AADAIController::StopAI()
{
	auto BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(BrainComponent);

	if (BehaviorTreeComponent != nullptr)
	{
		BehaviorTreeComponent->StopTree(EBTStopMode::Safe);
	}
}

void AADAIController::EnemyKill(class AADEnemyCharacter* _killedNpc) const
{
	if (warGameInstance_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : warGameInstance_"));
		return;
	}
	warGameInstance_->SetSaveExp(_killedNpc->GetExp());
}

void AADAIController::SetIsHit(bool _isHit)
{
	isHit_ = _isHit;
}

bool AADAIController::GetIsHit()
{
	return isHit_;
}