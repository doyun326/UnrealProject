// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Object/Interact/SpaceShipDeskInteract.h"
#include "../Public/GameSetting/WarGameInstance.h"
#include "../Public/UI/AIDeskInteractionWidget.h"

#include "Components/WidgetComponent.h"
#include "Engine/Engine.h"

#define TERMINAL_MESH_PATH	"/Game/StarterBundle/ModularSci_Comm/Meshes/SM_Terminal_A_UI.SM_Terminal_A_UI"
#define DIALOGUEWIDGET_PATH	"/Game/My/Blueprints/UI/DialogueWidget.DialogueWidget_C"

ASpaceShipDeskInteract::ASpaceShipDeskInteract()
{
	//Mesh ¼³Á¤
	terminalMesh_ = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TerminalMesh"));
	RootComponent = terminalMesh_;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> TERMINAL_MESH(TEXT(TERMINAL_MESH_PATH));

	if (TERMINAL_MESH.Succeeded())
	{
		ABLOG(Warning, TEXT("Success : TerminalMesh"));
		terminalMesh_->SetStaticMesh(TERMINAL_MESH.Object);
	}

	//Widget Setting
	dialogueWidgetClass_ = CreateDefaultSubobject<UWidgetComponent>(TEXT("Dialogue Widget"));
	static ConstructorHelpers::FClassFinder<UAIDeskInteractionWidget> DIALOGUE_WIDGET(TEXT(DIALOGUEWIDGET_PATH));

	if (DIALOGUE_WIDGET.Succeeded())
	{
		ABLOG(Warning, TEXT("Success : DIALOGUE_WIDGET"));
		dialogueWidgetClass_->SetWidgetClass(DIALOGUE_WIDGET.Class);
	}

	addViewportCheck_ = false;
	currentLineID_ = 1;
	conversation_ = 1;
	npcID_ = 1;
	rowNum_ = 0;
}

void ASpaceShipDeskInteract::BeginPlay()
{
	Super::BeginPlay();

	WarInstance_ = Cast<UWarGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (WarInstance_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : WarInstance"));
		return;
	}

	if (dialogueWidgetClass_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : dialogueWidgetClass"));
		return;
	}

	dialougeWidget_ = Cast<UAIDeskInteractionWidget>(dialogueWidgetClass_->GetUserWidgetObject());

	for (int RowNum = 1; RowNum <= WarInstance_->GetDialogueRowNums(); RowNum++)
	{
		struct FNpcDialogueData* Data = WarInstance_->GetDialogueData(RowNum);

		if (Data == nullptr)
		{
			ABLOG(Error, TEXT("Nullptr : NpcDialogueData"));
			return;
		}

		if (Data->NpcID == npcID_)
		{
			dialogueDatas_.Add(Data);
		}
	}
}

void ASpaceShipDeskInteract::Interact()
{
	if (!addViewportCheck_)
	{
		DialogueCreate();
	}
	else
	{
		ChangeDialogue();
	}

	if (dialougeTexts_.Num() - 1 > rowNum_)
	{
		rowNum_++;
	}
	else if (dialougeTexts_.Num() - 1 == rowNum_)
	{
		if (GetWorld() == nullptr)
		{
			ABLOG(Error, TEXT("Nullptr : World"));
			return;
		}
		GetWorld()->GetTimerManager().SetTimer(viewTimeHandler_, this, &ASpaceShipDeskInteract::RemoveWidget, 2.0f, false);
	}
}

void ASpaceShipDeskInteract::DialogueCreate()
{
	if (dialougeWidget_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : DialogueWidget"));
		return;
	}

	if (WarInstance_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : WarInstance"));
		return;
	}

	dialougeWidget_->AddToViewport();
	WarInstance_->SetCheckAddViewport(true);
	GetDialogueLine();
	addViewportCheck_ = true;
}

void ASpaceShipDeskInteract::GetDialogueLine()
{
	if (dialougeWidget_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : DialogueWidget"));
		return;
	}

	for(int32 DataNum = 0; DataNum < dialogueDatas_.Num(); DataNum++)
	{
		if (dialogueDatas_[DataNum]->NpcID == npcID_ && dialogueDatas_[DataNum]->LineID == currentLineID_)
		{
			dialougeTexts_.Add(dialogueDatas_[DataNum]->Dialogue);
		}
	}
	dialougeWidget_->SetDialogueText(dialougeTexts_);
}

void ASpaceShipDeskInteract::ChangeDialogue()
{
	if (addViewportCheck_)
	{
		if (dialougeWidget_ == nullptr)
		{
			ABLOG(Error, TEXT("Nullptr : DialogueWidget"));
			return;
		}
		dialougeWidget_->UpdateDialogueText(rowNum_);
	}
}

void ASpaceShipDeskInteract::RemoveWidget()
{
	if (WarInstance_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : WarInstance"));
		return;
	}

	dialougeWidget_->DialogueEmpty();
	dialougeWidget_->RemoveFromParent();
	addViewportCheck_ = false;
	WarInstance_->SetCheckAddViewport(false);
	GetWorld()->GetTimerManager().ClearTimer(viewTimeHandler_);
	dialougeTexts_.Empty();
	rowNum_ = 0;

	if (currentLineID_ == 1)
	{
		WarInstance_->ReserveShakeCamera(5);
	}
	else
	{
		UGameplayStatics::OpenLevel(this, FName("Stage_01"));
	}
	currentLineID_++;
}