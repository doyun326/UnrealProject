// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/GameSetting/Stage02LevelScript.h"
#include "../Public/GameSetting/WarGameInstance.h"

#include "LevelSequence/Public/LevelSequencePlayer.h"
#include "LevelSequence/Public/LevelSequence.h"
#include "DrawDebugHelpers.h"

AStage02LevelScript::AStage02LevelScript()
{
	rootComponent_ = CreateDefaultSubobject<USceneComponent>(TEXT("Root Component"));
	RootComponent = rootComponent_;

	//TriggerSetting - beginStartTrigger_
	beginStartTrigger_ = CreateDefaultSubobject<UBoxComponent>(TEXT("BeginTrigger"));
	beginStartTrigger_->SetBoxExtent(FVector(100.0f, 100.0f, 100.0f));	//Trigger Box Extent(ºÎÇÇ)
	beginStartTrigger_->SetupAttachment(RootComponent);
	beginStartTrigger_->SetRelativeLocation(FVector(-4847.0f, -26.0f, 89.0f)); //Trigger Box Location
	beginStartTrigger_->SetCollisionProfileName(TEXT("MapTrigger"));
	beginStartTrigger_->OnComponentBeginOverlap.AddDynamic(this, &AStage02LevelScript::OnBeginStartTriggerBeginOverlap);

	checkStart_ = false;
}

void AStage02LevelScript::BeginPlay()
{
	warInstance_ = Cast<UWarGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	
	if (warInstance_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : WarInstance"));
		return;
	}

#ifdef DRAW_DEBUGHELPER
	//WalkTrigger - Center, Extent
	DrawDebugBox(GetWorld(), FVector(-4847.0f, -26.0f, 89.0f), FVector(100.0f, 100.0f, 100.0f), FColor::Red, true, -1, 0, 10);
#endif //DRAW_DEBUGHELPER
}

void AStage02LevelScript::OnBeginStartTriggerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABLOG_S(Error);
	if (warInstance_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : WarInstance"));
		return;
	}
	if (!checkStart_)
	{
		warInstance_->StageViewWidgetStart(UGameplayStatics::GetCurrentLevelName(GetWorld()));
		checkStart_ = true;
	}
}