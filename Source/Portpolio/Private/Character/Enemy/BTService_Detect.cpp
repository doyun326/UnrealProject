// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Character/Enemy/BTService_Detect.h"
#include "../Public/Character/Enemy/ADAIController.h"
#include "../Public/Character/Player/PlayerCharacter.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "DrawDebugHelpers.h"

UBTService_Detect::UBTService_Detect()
{
	NodeName = TEXT("Detect");
	Interval = 1.0f;
}

void UBTService_Detect::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();

	if (ControllingPawn == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : Controlling Pawn"));
		return;
	}

	auto Controller = Cast<AADAIController>(ControllingPawn->GetController());

	if (Controller == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : ADAIController"));
		return;
	}

	UWorld* World = ControllingPawn->GetWorld();

	if (World == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : World"));
		return;
	}

	FVector Center = ControllingPawn->GetActorLocation();
	float	DetectRadius;

	if (Controller->GetIsHit())
	{
		DetectRadius = 4000.0f;
	}
	else
	{
		DetectRadius = 600.0f;
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
				OwnerComp.GetBlackboardComponent()->SetValueAsObject(AADAIController::targetKey_, Player);

#ifdef	DRAW_DEBUGHELPER
				{
					DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Green, false, 0.2f);
					DrawDebugPoint(World, Player->GetActorLocation(), 10.0f, FColor::Blue, false, 0.2f);
					DrawDebugLine(World, ControllingPawn->GetActorLocation(), Player->GetActorLocation(), FColor::Blue, false, 0.2f);
				}
#endif	//DRAW_DEBUGHELPER
				return;
			}
		}
	}
	else
	{
		OwnerComp.GetBlackboardComponent()->SetValueAsObject(AADAIController::targetKey_, nullptr);
	} 
#ifdef	DRAW_DEBUGHELPER
	{
		if (Controller->GetIsHit())
		{
			DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Blue, false, 0.2f);
		}
		else
		{
			DrawDebugSphere(World, Center, DetectRadius, 16, FColor::Red, false, 0.2f);
		}
	}
#endif	//DRAW_DEBUGHELPER
}
