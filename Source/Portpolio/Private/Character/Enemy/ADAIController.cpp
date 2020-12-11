// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/Character/Enemy/ADAIController.h"

#include "NavigationSystem.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

AADAIController::AADAIController()
{
	repeatInterval_ = 3.0f;
}

void AADAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	GetWorld()->GetTimerManager().SetTimer(repeatTimerHandle_, this, &AADAIController::OnRepeatTimer, repeatInterval_, true);
}

void AADAIController::OnUnPossess()
{
	Super::OnUnPossess();

	GetWorld()->GetTimerManager().ClearTimer(repeatTimerHandle_);
}

void AADAIController::OnRepeatTimer()
{
	auto CurrentPawn = GetPawn();

	if (CurrentPawn == nullptr)
	{
		return;
	}

	UNavigationSystemV1* NavSystem = UNavigationSystemV1::GetNavigationSystem(GetWorld());

	if (NavSystem == nullptr)
	{
		return;
	}

	FNavLocation NextLocation;

	if (NavSystem->GetRandomPointInNavigableRadius(FVector::ZeroVector, 500.0f, NextLocation))
	{
		UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, NextLocation.Location);
		ABLOG(Warning, TEXT("Next Location : %s"), *NextLocation.Location.ToString());
	}
}