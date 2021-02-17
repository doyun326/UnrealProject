// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSetting/Portpolio.h"

#include "Engine/LevelScriptActor.h"
#include "Stage01LevelScript.generated.h"

/**
 * 
 */
UCLASS()
class PORTPOLIO_API AStage01LevelScript : public ALevelScriptActor
{
	GENERATED_BODY()
	
public:
	AStage01LevelScript();

protected:
	virtual void BeginPlay();

private:
	UPROPERTY()
		class ULevelSequencePlayer*	SequencePlayer;
	UPROPERTY(EditAnywhere)
		class ULevelSequence*		SequenceAsset;
};
