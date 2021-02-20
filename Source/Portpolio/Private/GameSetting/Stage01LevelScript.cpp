// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/GameSetting/Stage01LevelScript.h"
#include "../Public/GameSetting/WarGameInstance.h"

#include "LevelSequence/Public/LevelSequencePlayer.h"
#include "LevelSequence/Public/LevelSequence.h"
#include "DrawDebugHelpers.h"

#define STAGE01_SEQUENCE_PATH "/Game/My/Cinematics/Stage01/Stage01_Master.Stage01_Master"

AStage01LevelScript::AStage01LevelScript()
{
	//TriggerSetting
	walkTrigger_ = CreateDefaultSubobject<UBoxComponent>(TEXT("WalkTrigger"));
	walkTrigger_->SetBoxExtent(FVector(3500.0f, 200.0f, 200.0f));
	walkTrigger_->SetupAttachment(RootComponent);
	walkTrigger_->SetRelativeLocation(FVector(4000.0f, 4900.0f, 200.0f)); //Trigger Box Location
	walkTrigger_->SetCollisionProfileName(TEXT("MapTrigger"));

	walkTrigger_->OnComponentBeginOverlap.AddDynamic(this, &AStage01LevelScript::OnTriggerBeginOverlap);

	checkGo_ = false;
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
		//sequencePlayer_->Play();
	}

	//WalkTrigger - Center, Extent
	//DrawDebugBox(GetWorld(), FVector(4000.0f, 4900.0f, 200.0f), FVector(3500.0f, 200.0f, 200.0f), FColor::Red, true, -1, 0, 10);

	warInstance_ = Cast<UWarGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	//GetWorld()->GetTimerManager().SetTimer(startWidgetHandler_, this, &AStage01LevelScript::WidgetStart, 10.5f, false);

	//빠른 진행을 위한 일단 스킵
	WidgetStart();
}

void AStage01LevelScript::WidgetStart()
{
	if (warInstance_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : WarInstance"));
		return;
	}
	warInstance_->StageViewWidgetStart(UGameplayStatics::GetCurrentLevelName(GetWorld()));
}

void AStage01LevelScript::OnTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!checkGo_)
	{
		if (warInstance_ == nullptr)
		{
			ABLOG(Error, TEXT("Nullptr : WarInstance"));
			return;
		}
		warInstance_->StageViewWidgetStart(UGameplayStatics::GetCurrentLevelName(GetWorld()));
		checkGo_ = true;
	}
}