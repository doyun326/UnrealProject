// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/GameSetting/Stage01LevelScript.h"

#include "LevelSequence/Public/LevelSequencePlayer.h"
#include "LevelSequence/Public/LevelSequence.h"

#define STAGE01_SEQUENCE_PATH "/Game/My/Cinematics/Stage01/Stage01_Master.Stage01_Master"

AStage01LevelScript::AStage01LevelScript()
{
	
}

void AStage01LevelScript::BeginPlay()
{
	Super::BeginPlay();

	FStringAssetReference SequenceName(TEXT(STAGE01_SEQUENCE_PATH));
	ALevelSequenceActor* currentLevelSequenceActor = nullptr;

	SequenceAsset = Cast<ULevelSequence>(SequenceName.TryLoad());
	SequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), SequenceAsset, FMovieSceneSequencePlaybackSettings(), currentLevelSequenceActor);

	if (SequencePlayer)
	{
		SequencePlayer->Play();
	}
	
	ABLOG(Error, TEXT("%f"), SequencePlayer->GetLength());
	//SequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), SequenceAsset, FMovieSceneSequencePlaybackSettings());
}