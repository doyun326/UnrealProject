// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Character/Npc/NpcOperator.h"
#include "../Public/Character/Npc//NpcOperatorAnimInstance.h"
#include "../Public/Character/Player/PlayerCharacter.h"
#include "../Public/GameSetting/WarGameInstance.h"
#include "../Public/UI/AIDeskInteractionWidget.h"

#include "Components/WidgetComponent.h"
#include "Components/SphereComponent.h"

#define OPERATORMESH_PATH	"/Game/My/Asset/Character/Operator/Original_Bone/Idle.Idle"
#define OPERANIM_PATH		"/Game/My/Blueprints/Anim/Npc/OperAnim_BP.OperAnim_BP_C"
#define DIALOGUEWIDGET_PATH	"/Game/My/Blueprints/UI/DialogueWidget.DialogueWidget_C"

ANpcOperator::ANpcOperator()
{
	PrimaryActorTick.bCanEverTick = true;

	//Operator Mesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> OPER_MESH(TEXT(OPERATORMESH_PATH));

	if (OPER_MESH.Succeeded())
	{
		ABLOG(Warning, TEXT("Success : OPER_MESH"));
		GetMesh()->SetSkeletalMesh(OPER_MESH.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -95.0f), FRotator(0.0f, -90.0f, 0.0f));
		GetMesh()->SetRelativeScale3D(FVector(3.0f, 3.0f, 3.0f));
	}

	//Operator AnimInstance
	static ConstructorHelpers::FClassFinder<UNpcOperatorAnimInstance> OPER_ANIM(TEXT(OPERANIM_PATH));

	if (OPER_ANIM.Succeeded())
	{
		ABLOG(Warning, TEXT("Success : OPER_ANIM"));
		GetMesh()->SetAnimInstanceClass(OPER_ANIM.Class);
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
	effectCheck_ = false;	
	currentLineID_ = 1;
	conversation_ = 1;
	npcID_ = 2;
	rowNum_ = 0;
	remainNum_ = 4;
}

void ANpcOperator::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ANpcOperator::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void ANpcOperator::BeginPlay()
{
	Super::BeginPlay();

	operAnim_ = Cast<UNpcOperatorAnimInstance>(GetMesh()->GetAnimInstance());

	if (operAnim_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : operAnim"));
		return;
	}

	warInstance_ = Cast<UWarGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

	if (warInstance_ == nullptr)
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

	for (int RowNum = 1; RowNum <= warInstance_->GetDialogueRowNums(); RowNum++)
	{
		struct FNpcDialogueData* Data = warInstance_->GetDialogueData(RowNum);

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

	warInstance_->onViewWidget.AddUObject(this, &ANpcOperator::ViewWidget);
}

void ANpcOperator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ACharacter* myCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
}

void ANpcOperator::ViewWidget()
{
	DialogueCreate();
}

void ANpcOperator::DialogueCreate()
{
	if (dialougeWidget_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : DialogueWidget"));
		return;
	}

	if (warInstance_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : WarInstance"));
		return;
	}
	dialougeWidget_->AddToViewport();

	for (int32 DataNum = 0; DataNum < dialogueDatas_.Num(); DataNum++)
	{
		if (dialogueDatas_[DataNum]->NpcID == npcID_ && dialogueDatas_[DataNum]->LineID == currentLineID_)
		{
			dialougeTexts_.Add(dialogueDatas_[DataNum]->Dialogue);
		}
	}

	if (dialougeTexts_.Num() == 0)
	{
		ABLOG(Error, TEXT("dialogueTexts_ Zero"));
		return;
	}

	dialougeWidget_->SetDialogueText(dialougeTexts_);
	rowNum_++;

	if (GetWorld() == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : GetWorld()"));
		return;
	}

	if (currentLineID_ == 1 && UGameplayStatics::GetCurrentLevelName(GetWorld()) == "Stage_01")
	{
		GetWorld()->GetTimerManager().SetTimer(effectTimeHandler_, this, &ANpcOperator::ControllPlayerEffect, 0.3f, true, 1.0f);
	}
	GetWorld()->GetTimerManager().SetTimer(viewTimeHandler_, this, &ANpcOperator::ChangeDialogue, 2.5f, true);
}

void ANpcOperator::ChangeDialogue()
{
	if (dialougeWidget_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : dialogueWidget"));
		return;
	}

	dialougeWidget_->UpdateDialogueText(rowNum_);

	if (dialougeTexts_.Num() - 1 > rowNum_)
	{
		rowNum_++;

		if (currentLineID_ == 2 && rowNum_ == 3)
		{
			GetWorld()->GetTimerManager().SetTimer(effectTimeHandler_, this, &ANpcOperator::ControllPlayerEffect, 0.3f, true, 1.0f);
		}
	}
	else if (dialougeTexts_.Num() - 1 == rowNum_)
	{
		if (GetWorld() == nullptr)
		{
			ABLOG(Error, TEXT("Nullptr : World"));
			return;
		}
		GetWorld()->GetTimerManager().SetTimer(viewTimeHandler_, this, &ANpcOperator::RemoveWidget, 2.0f, false);
	}
}

void ANpcOperator::ControllPlayerEffect()
{
	if (currentLineID_ == 1)
	{
		warInstance_->ActiveFlashEffect();
	}
	else if (currentLineID_ == 2)
	{
		warInstance_->ActiveLimitEffect();
	}

	if (--remainNum_ < 0)
	{
		GetWorld()->GetTimerManager().ClearTimer(effectTimeHandler_);
		effectCheck_ = true;
		remainNum_ = 4;
	}
}

void ANpcOperator::RemoveWidget()
{
	if (dialougeWidget_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : dialougeWidget"))
		return;
	}

	dialougeWidget_->DialogueEmpty();
	dialougeWidget_->RemoveFromParent();
	dialougeTexts_.Empty();
	currentLineID_++;
	rowNum_ = 0;
}