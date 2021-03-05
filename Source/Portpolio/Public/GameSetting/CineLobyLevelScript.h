// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSetting/Portpolio.h"

#include "Engine/LevelScriptActor.h"
#include "CineLobyLevelScript.generated.h"

/**
 * 
 */
UCLASS()
class PORTPOLIO_API ACineLobyLevelScript : public ALevelScriptActor
{
	GENERATED_BODY()
	
public:
	ACineLobyLevelScript();

protected:
	virtual void BeginPlay() override;

private:
	void	NextLevel();

	UPROPERTY()
		class UWarGameInstance* warInstance_;
	UPROPERTY()
		class ULevelSequencePlayer* sequencePlayer_;
	UPROPERTY(EditAnywhere)
		class ULevelSequence* sequenceAsset_;
	UPROPERTY(VisibleAnywhere, Category = "Trigger", meta = (AllowPrivateAccess = true))
		UBoxComponent* walkTrigger_;
	UPROPERTY(VisibleAnywhere, Category = "Trigger", meta = (AllowPrivateAccess = true))
		UBoxComponent* mapFrontTrigger_;
	UPROPERTY(VisibleAnywhere, Category = "Trigger", meta = (AllowPrivateAccess = true))
		UBoxComponent* nextMapTrigger_;

	FTimerHandle startTimeHandler_;
};
