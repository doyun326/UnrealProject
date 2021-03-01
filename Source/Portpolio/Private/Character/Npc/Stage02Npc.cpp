// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Character/Npc/Stage02Npc.h"
#include "../Public/GameSetting/WarGameInstance.h"
#include "../Public/UI/AIDeskInteractionWidget.h"

#include "Components/WidgetComponent.h"

#define DIALOGUEWIDGET_PATH	"/Game/My/Blueprints/UI/DialogueWidget.DialogueWidget_C"

AStage02Npc::AStage02Npc()
{
	//Widget Setting
	/*dialogueWidgetClass_ = CreateDefaultSubobject<UWidgetComponent>(TEXT("Dialogue Widget"));
	static ConstructorHelpers::FClassFinder<UAIDeskInteractionWidget> DIALOGUE_WIDGET(TEXT(DIALOGUEWIDGET_PATH));

	if (DIALOGUE_WIDGET.Succeeded())
	{
		ABLOG(Warning, TEXT("Success : DIALOGUE_WIDGET"));
		dialogueWidgetClass_->SetWidgetClass(DIALOGUE_WIDGET.Class);
	}*/

	npcID_ = 3;
	currentLineID_ = 1;
}

void AStage02Npc::BeginPlay()
{
	Super::BeginPlay();

	warInstance_ = Cast<UWarGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (warInstance_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : WarInstance"));
		return;
	}

	warInstance_->onViewWidget02.AddUObject(this, &AStage02Npc::ViewWidget);
}

void AStage02Npc::ViewWidget()
{
	DialogueCreate();
}