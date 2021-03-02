// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Character/Enemy/Minion/BTService_MinionDetect.h"
#include "../Public/Character/Enemy/Minion/MinionAIController.h"
#include "../Public/Character/Player/PlayerCharacter.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

#define DETECT_RADIUS 600.0f

UBTService_MinionDetect::UBTService_MinionDetect()
{
	NodeName = TEXT("MinionDetect");
	Interval = 1.0f;
}

void UBTService_MinionDetect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();

	if (ControllingPawn == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : Controlling Pawn"));
		return;
	}

	auto Controller = Cast<AMinionAIController>(ControllingPawn->GetController());

	if (Controller == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : MinionAIController"));
		return;
	}

	UWorld* World = ControllingPawn->GetWorld();
	FVector Center = ControllingPawn->GetActorLocation();
	float	DetectRadius;

	if (Controller->GetIsHit())
	{
		DetectRadius = 4000.0f;
	}
	else
	{
		DetectRadius = DETECT_RADIUS;
	}

	if (World == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : World"));
		return;
	}

	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingPawn);

	//PlayerÃ£±â
	bool bResult = World->OverlapMultiByChannel(
		OverlapResults,
		Center,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel1,
		FCollisionShape::MakeSphere(DetectRadius),
		CollisionQueryParam
	);

	if (bResult)
	{
		for (auto OverlapResult : OverlapResults)
		{
			APlayerCharacter* Player = Cast<APlayerCharacter>(OverlapResult.GetActor());

			if (Player)
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(AMinionAIController::targetKey_, Player);

#ifdef DRAW_DEBUGHELPER
				{
					DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 0.2f);
					DrawDebugPoint(World, Player->GetActorLocation(), 10.0f, FColor::Blue, false, 0.2f);
					DrawDebugLine(World, ControllingPawn->GetActorLocation(), Player->GetActorLocation(), FColor::Blue, false, 0.2f);
				}
#endif
				return;
			}
		}
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(AMinionAIController::targetKey_, nullptr);
	}
	//ABLOG(Warning, TEXT("%d"), bResult);
	DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2f);
}