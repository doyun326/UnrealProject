// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Character/Enemy/Boss/BTBossService_Detect.h"
#include "../Public/Character/Enemy/Boss/BossAIController.h"
#include "../Public/Character/Player/PlayerCharacter.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

UBTBossService_Detect::UBTBossService_Detect()
{
	NodeName = TEXT("Detect");
	Interval = 1.0f;
}

void UBTBossService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();

	if (ControllingPawn == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : Controlling Pawn"));
		return;
	}

	UWorld* World = ControllingPawn->GetWorld();
	FVector Center = ControllingPawn->GetActorLocation();
	float	DetectRadius = 600.0f;

	if (World == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : World"));
		return;
	}

	TArray<FOverlapResult> OverlapResults;
	FCollisionQueryParams CollisionQueryParam(NAME_None, false, ControllingPawn);

	//Playerã��
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
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(ABossAIController::targetKey_, Player);
				DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 0.2f);
				DrawDebugPoint(World, Player->GetActorLocation(), 10.0f, FColor::Blue, false, 0.2f);
				DrawDebugLine(World, ControllingPawn->GetActorLocation(), Player->GetActorLocation(), FColor::Blue, false, 1.2f);
				return;
			}
		}
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(ABossAIController::targetKey_, nullptr);
	}
	//ABLOG(Warning, TEXT("%d"), bResult);
	DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2f);
}