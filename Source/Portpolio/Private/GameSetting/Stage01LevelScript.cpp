// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/GameSetting/Stage01LevelScript.h"
#include "../Public/GameSetting/WarGameInstance.h"

#include "LevelSequence/Public/LevelSequencePlayer.h"
#include "LevelSequence/Public/LevelSequence.h"
#include "DrawDebugHelpers.h"

#define STAGE01_SEQUENCE_PATH "/Game/My/Cinematics/Stage01/Stage01_Master.Stage01_Master"

AStage01LevelScript::AStage01LevelScript()
{
	rootComponent_ = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	RootComponent = rootComponent_;

	//TriggerSetting - WalkTrigger
	walkTrigger_ = CreateDefaultSubobject<UBoxComponent>(TEXT("WalkTrigger"));
	walkTrigger_->SetBoxExtent(FVector(3500.0f, 200.0f, 200.0f));
	walkTrigger_->SetupAttachment(RootComponent);
	walkTrigger_->SetRelativeLocation(FVector(4000.0f, 4900.0f, 200.0f)); //Trigger Box Location
	walkTrigger_->SetCollisionProfileName(TEXT("MapTrigger"));
	walkTrigger_->OnComponentBeginOverlap.AddDynamic(this, &AStage01LevelScript::OnTriggerBeginOverlap);

	//TriggerSetting - NextMapTrigger
	nextMapTrigger_ = CreateDefaultSubobject<UBoxComponent>(TEXT("NextMapTrigger"));
	nextMapTrigger_->SetBoxExtent(FVector(100.0f, 100.0f, 200.0f));
	nextMapTrigger_->SetupAttachment(RootComponent);
	nextMapTrigger_->SetRelativeLocation(FVector(-5025.0f, 7235.0f, 500.0f)); //Trigger Box Location
	nextMapTrigger_->SetCollisionProfileName(TEXT("MapTrigger"));
	nextMapTrigger_->OnComponentBeginOverlap.AddDynamic(this, &AStage01LevelScript::OnNextMapTriggerBeginOverlap);

	//TriggerSetting - mapFrontTrigger
	mapFrontTrigger_ = CreateDefaultSubobject<UBoxComponent>(TEXT("MapFrontTrigger"));
	mapFrontTrigger_->SetBoxExtent(FVector(500.0f, 500.0f, 200.0f));
	mapFrontTrigger_->SetupAttachment(RootComponent);
	mapFrontTrigger_->SetRelativeLocation(FVector(-2607.0f, 6336.0f, 171.0f)); //Trigger Box Location
	mapFrontTrigger_->SetCollisionProfileName(TEXT("MapTrigger"));
	mapFrontTrigger_->OnComponentBeginOverlap.AddDynamic(this, &AStage01LevelScript::OnMapFrontTriggerBeginOverlap);

	checkGo_ = false;
	checkMapFront_ = false;
}

void AStage01LevelScript::BeginPlay()
{
	Super::BeginPlay();
	
	FStringAssetReference SequenceName(TEXT(STAGE01_SEQUENCE_PATH));
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

	if (sequencePlayer_)
	{
		//sequencePlayer_->Play();
	}

#ifdef DRAW_DEBUGHELPER
	//WalkTrigger - Center, Extent
	DrawDebugBox(GetWorld(), FVector(4000.0f, 4900.0f, 200.0f), FVector(3500.0f, 200.0f, 200.0f), FColor::Red, true, -1, 0, 10);
	//NextMapTrigger - Center, Extent
	DrawDebugBox(GetWorld(), FVector(-5025.0f, 7235.0f, 500.0f), FVector(100.0f, 100.0f, 200.0f), FColor::Blue, true, -1, 0, 10);
	//MapFrontTrigger - Center, Extent
	DrawDebugBox(GetWorld(), FVector(-2607.0f, 6336.0f, 171.0f), FVector(500.0f, 500.0f, 200.0f), FColor::Green, true, -1, 0, 10);
#endif //DRAW_DEBUGHELPER

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

void AStage01LevelScript::OnMapFrontTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!checkMapFront_)
	{
		ABLOG_S(Error);

		if (warInstance_ == nullptr)
		{
			ABLOG(Error, TEXT("Nullptr : WarInstance"));
			return;
		}
		warInstance_->StageViewWidgetStart(UGameplayStatics::GetCurrentLevelName(GetWorld()));
		checkMapFront_ = true;
	}
}

void AStage01LevelScript::OnNextMapTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UGameplayStatics::OpenLevel(this, FName("Stage_02"));
}