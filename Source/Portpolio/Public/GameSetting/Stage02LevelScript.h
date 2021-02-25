// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSetting/Portpolio.h"

#include "Engine/LevelScriptActor.h"
#include "Stage02LevelScript.generated.h"

/**
 * 
 */
UCLASS()
class PORTPOLIO_API AStage02LevelScript : public ALevelScriptActor
{
	GENERATED_BODY()
	
public:
	AStage02LevelScript();

protected:
	virtual void BeginPlay();

private:
};
