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
	currentLineID_ = 1;
	conversation_ = 1;
	npcID_ = 2;
	rowNum_ = 0;
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

void ANpcOperator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ACharacter* myCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
}