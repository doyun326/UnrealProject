// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/GameSetting/Stage01LevelScript.h"
#include "../Public/GameSetting/WarGameInstance.h"

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

	sequenceAsset_ = Cast<ULevelSequence>(SequenceName.TryLoad());
	sequencePlayer_ = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), sequenceAsset_, FMovieSceneSequencePlaybackSettings(), currentLevelSequenceActor);

	if (sequenceAsset_ == nullptr || sequencePlayer_ == nullptr)
	{
		ABLOG(Error, TEXT("Error : sequence"));
		return;
	}

	if (sequencePlayer_)
	{
		sequencePlayer_->Play();
	}

	warInstance_ = Cast<UWarGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	GetWorld()->GetTimerManager().SetTimer(startWidgetHandler_, this, &AStage01LevelScript::WidgetStart, 10.5f, false);
}

void AStage01LevelScript::WidgetStart()
{
	if (warInstance_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : WarInstance"));
		return;
	}
	warInstance_->StageStart(UGameplayStatics::GetCurrentLevelName(GetWorld()));
}