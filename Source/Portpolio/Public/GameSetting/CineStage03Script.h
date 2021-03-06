// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSetting/Portpolio.h"

#include "Engine/LevelScriptActor.h"
#include "CineStage03Script.generated.h"

/**
 * 
 */
UCLASS()
class PORTPOLIO_API ACineStage03Script : public ALevelScriptActor
{
	GENERATED_BODY()
	
public:
	ACineStage03Script();

protected:
	virtual void BeginPlay() override;

private:
	void	OpenLevel();

	UPROPERTY()
		class UWarGameInstance*		warInstance_;
	UPROPERTY()
		class ULevelSequencePlayer* sequencePlayer_;
	UPROPERTY(EditAnywhere)
		class ULevelSequence*		sequenceAsset_;

	FTimerHandle openLevelTimer_;
};
