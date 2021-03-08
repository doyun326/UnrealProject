// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/GameSetting/CineStage03Script.h"
#include "../Public/GameSetting/WarGameInstance.h"

#include "LevelSequence/Public/LevelSequencePlayer.h"
#include "LevelSequence/Public/LevelSequence.h"

#define STAGE03_SEQUENCE_PATH	"/Game/My/Cinematics/CIneStage03/CineStage03_Master.CineStage03_Master"
#define FADEINOUT_PATH			"/Game/My/Cinematics/FadeInOut/FadeOutIn.FadeOutIn"

ACineStage03Script::ACineStage03Script()
{

}

void ACineStage03Script::BeginPlay()
{
	Super::BeginPlay();

	FStringAssetReference SequenceName(TEXT(STAGE03_SEQUENCE_PATH));
	ALevelSequenceActor* currentLevelSequenceActor = nullptr;

	FStringAssetReference FadeInOutName(TEXT(FADEINOUT_PATH));
	ALevelSequenceActor* FadeInOutSequenceActor = nullptr;

	warInstance_ = Cast<UWarGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (warInstance_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : WarInstance"));
		return;
	}

	sequenceAsset_ = Cast<ULevelSequence>(SequenceName.TryLoad()); 
	sequencePlayer_ = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), sequenceAsset_, FMovieSceneSequencePlaybackSettings(), currentLevelSequenceActor);

	fadeInOutAsset_ = Cast<ULevelSequence>(FadeInOutName.TryLoad());
	fadeInOutPlayer_ = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), fadeInOutAsset_, FMovieSceneSequencePlaybackSettings(), FadeInOutSequenceActor);

	if (sequenceAsset_ == nullptr || sequencePlayer_ == nullptr)
	{
		ABLOG(Error, TEXT("Error : sequence"));
		return;
	}

	if (fadeInOutPlayer_ == nullptr || fadeInOutAsset_ == nullptr)
	{
		ABLOG(Error, TEXT("Error : seqence"));
		return;
	}

	if (sequencePlayer_)
	{
		warInstance_->SetPlayingSequence(true);
		sequencePlayer_->Play();
	}
	GetWorld()->GetTimerManager().SetTimer(openLevelTimer_, this, &ACineStage03Script::FadeInOut, 7.0f, false);
}

void ACineStage03Script::FadeInOut()
{
	GetWorld()->GetTimerManager().ClearTimer(openLevelTimer_);
	fadeInOutPlayer_->Play();
	GetWorld()->GetTimerManager().SetTimer(openLevelTimer_, this, &ACineStage03Script::OpenLevel, 1.7f, false);
}

void ACineStage03Script::OpenLevel()
{
	warInstance_->SetPlayingSequence(false);
	UGameplayStatics::OpenLevel(this, FName("Stage_03"));
}