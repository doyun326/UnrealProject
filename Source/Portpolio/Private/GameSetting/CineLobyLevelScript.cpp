// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/GameSetting/CineLobyLevelScript.h"
#include "../Public/GameSetting/WarGameInstance.h"

#include "Components/WidgetComponent.h"
#include "LevelSequence/Public/LevelSequencePlayer.h"
#include "LevelSequence/Public/LevelSequence.h"
#include "DrawDebugHelpers.h"

#define CINELOBY_SEQUENCE_PATH "/Game/My/Cinematics/StageLoby/StageLoby_Master.StageLoby_Master"

ACineLobyLevelScript::ACineLobyLevelScript()
{

}

void ACineLobyLevelScript::BeginPlay()
{
	Super::BeginPlay();

	FStringAssetReference SequenceName(TEXT(CINELOBY_SEQUENCE_PATH));
	ALevelSequenceActor* currentLevelSequenceActor = nullptr;

	warInstance_ = Cast<UWarGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (warInstance_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : WarInstance"));
		return;
	}

	sequenceAsset_ = Cast<ULevelSequence>(SequenceName.TryLoad());
	sequencePlayer_ = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), sequenceAsset_, FMovieSceneSequencePlaybackSettings(), currentLevelSequenceActor);

	if (sequenceAsset_ == nullptr || sequencePlayer_ == nullptr)
	{
		ABLOG(Error, TEXT("Error : sequence"));
		return;
	}

	warInstance_->SetPlayingSequence(true);

	if (sequencePlayer_)
	{
		sequencePlayer_->Play();
	}

	GetWorld()->GetTimerManager().SetTimer(startTimeHandler_, this, &ACineLobyLevelScript::NextLevel, 8.3f, false);
}

void ACineLobyLevelScript::NextLevel()
{
	warInstance_->SetPlayingSequence(false);
	UGameplayStatics::OpenLevel(this, FName("SpaceShip_Loby"));
}