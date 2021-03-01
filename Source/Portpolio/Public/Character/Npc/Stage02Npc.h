// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSetting/Portpolio.h"

#include "Character/Npc/NpcOperator.h"
#include "Stage02Npc.generated.h"

/**
 * 
 */
UCLASS()
class PORTPOLIO_API AStage02Npc : public ANpcOperator
{
	GENERATED_BODY()

public:
	AStage02Npc();

	void ViewWidget();
	
protected:
	virtual void BeginPlay() override;

private:
	
};
