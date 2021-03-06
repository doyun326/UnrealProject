// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSetting/Portpolio.h"

#include "Engine/LevelScriptActor.h"
#include "StageLobyLevelScript.generated.h"

/**
 * 
 */
UCLASS()
class PORTPOLIO_API AStageLobyLevelScript : public ALevelScriptActor
{
	GENERATED_BODY()
	
public:
	AStageLobyLevelScript();

protected: 
	virtual void BeginPlay() override;

private:

};
