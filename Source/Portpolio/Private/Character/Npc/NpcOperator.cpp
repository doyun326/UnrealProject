// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Character/Npc/NpcOperator.h"
#include "../Public/Character/Npc//NpcOperatorAnimInstance.h"
#include "../Public/Character/Player/PlayerCharacter.h"

#include "Components/WidgetComponent.h"
#include "Components/SphereComponent.h"

#define OPERATORMESH_PATH	"/Game/My/Asset/Character/Operator/Original_Bone/Idle.Idle"
#define OPERANIM_PATH		"/Game/My/Blueprints/Anim/Npc/OperAnim_BP.OperAnim_BP_C"
//#define PRESSEBTN_PATH		"/Game/My/Blueprints/UI/Npc/NpcInteractUI.NpcInteractUI_C"
#define PRESSEBTN_PATH		"/Game/My/Blueprints/UI/EnemyHpBar_UI.EnemyHpBar_UI_C"

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

	//Press Widget 설정
	pressWidgetComponent_ = CreateDefaultSubobject<UWidgetComponent>(TEXT("PressWidget"));
	pressWidgetComponent_->SetupAttachment(GetMesh());
	pressWidgetComponent_->SetRelativeLocation(FVector(0.0f, 0.0f, 200.0f));
	pressWidgetComponent_->SetWidgetSpace(EWidgetSpace::Screen);

	static ConstructorHelpers::FClassFinder<UUserWidget> UI_PRESS(TEXT(PRESSEBTN_PATH));

	if (UI_PRESS.Succeeded())
	{
		ABLOG(Warning, TEXT("Success : UI_PRESS"));

		pressWidgetComponent_->SetWidgetClass(UI_PRESS.Class);
		pressWidgetComponent_->SetDrawSize(FVector2D(120.0f, 50.0f));
	}

	//Overlap Collision
	collisionSphere_ = CreateDefaultSubobject<USphereComponent>(TEXT("GetCollisionSphere"));
	collisionSphere_->SetupAttachment(this->GetCapsuleComponent());
	collisionSphere_->InitSphereRadius(100.0f);

	collisionSphere_->OnComponentBeginOverlap.AddDynamic(this, &ANpcOperator::OnOverlapBegin);
	collisionSphere_->OnComponentEndOverlap.AddDynamic(this, &ANpcOperator::OnOverlapEnd);

	isTouch_ = false;
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

	//UI 연결(4.21ver 이 후, PostInitializeComponents()가 아닌 Widget초기화를 BeginPlay에서 한다.)
	/*if (pressWidgetComponent_ != nullptr)
	{
		ABLOG(Warning, TEXT("PressWidgetComponent"));
		pressWidget_ = Cast<UUserWidget>(pressWidgetComponent_->GetUserWidgetObject());

		if (pressWidget_ == nullptr)
		{
			ABLOG(Error, TEXT("Nullptr : pressWidget_"));
			return;
		}
	}*/
}

void ANpcOperator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ACharacter* myCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
}

void ANpcOperator::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!isTouch_)
	{
		isTouch_ = true;
		ABLOG(Warning, TEXT("Touch"));
	}

	ABLOG(Warning, TEXT("%s"), *(OtherActor->GetName()));
}

void ANpcOperator::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (isTouch_)
	{
		isTouch_ = false;
		ABLOG(Warning, TEXT("End Touch"));
	}
}