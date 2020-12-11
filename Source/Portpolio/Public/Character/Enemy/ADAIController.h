// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSetting/Portpolio.h"
#include "AIController.h"
#include "ADAIController.generated.h"

/**
 * 
 */
UCLASS()
class PORTPOLIO_API AADAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	AADAIController();

	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;

private:
	void	OnRepeatTimer();

	FTimerHandle	repeatTimerHandle_;
	float			repeatInterval_;
};
