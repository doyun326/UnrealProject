// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Character/Enemy/ADEnemyCharacter.h"
#include "../Public/Character/Enemy/ADAIController.h"
#include "../Public/Character/Enemy/ADAnimInstance.h"
#include "../Public/Character/Enemy/ADEnemyStatComponent.h"
#include "../Public/UI/EnemyHPWidget.h"

#include "Components/WidgetComponent.h"

#define TEST_ENEMYMESH_PATH	"/Game/My/Asset/Character/Enemy/AD/mutant/mutant.mutant"
#define ADANIM_PATH			"/Game/My/Blueprints/Anim/Enemy/ADAnim_BP.ADAnim_BP_C"

AADEnemyCharacter::AADEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	//AD Class를 Default로 지정
	AIControllerClass = AADAIController::StaticClass();
	//AI컨트롤러에 자동배치
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	//EnemyMesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> AD_ENEMY(TEXT(TEST_ENEMYMESH_PATH));

	if (AD_ENEMY.Succeeded())
	{
		GetMesh()->SetSkeletalMesh((AD_ENEMY.Object));
	}

	//Animation 설정
	static ConstructorHelpers::FClassFinder<UADAnimInstance> AD_ANIM(TEXT(ADANIM_PATH));

	if (AD_ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AD_ANIM.Class);
	}

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -95.0f), FRotator(0.0f, -90.0f, 0.0f));

	//EnemyStat 설정
	enemyStat_ = CreateDefaultSubobject<UADEnemyStatComponent>(TEXT("ADENEMYSTAT"));

	if (enemyStat_ ==  nullptr)
	{
		ABLOG(Warning, TEXT("EnemyStat Error"));
	}

	//HPBar설정
	HPBarWidget_ = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBARWIDGET"));
	HPBarWidget_->SetupAttachment(GetMesh());
	HPBarWidget_->SetRelativeLocation(FVector(0.0f, 0.0f, 200.0f));
	HPBarWidget_->SetWidgetSpace(EWidgetSpace::Screen);

	test = HPBarWidget_->GetWorld();

	static ConstructorHelpers::FClassFinder<UUserWidget> UI_ENEMYHP(TEXT("/Game/My/Asset/UI/EnemyHpBar_UI.EnemyHpBar_UI_C"));

	if (UI_ENEMYHP.Succeeded())
	{
		HPBarWidget_->SetWidgetClass(UI_ENEMYHP.Class);
		HPBarWidget_->SetDrawSize(FVector2D(120.0f, 50.0f));
		ABLOG(Warning, TEXT("UI_ENEMY is not nullptr"));
	}
} 

void AADEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	//HPBar 연결(4.21ver 이 후, PostInitializeComponents()가 아닌 Widget초기화를 BeginPlay에서 한다.
	auto EnemyHpWidget = Cast<UEnemyHPWidget>(HPBarWidget_->GetUserWidgetObject());

	if (EnemyHpWidget != nullptr)
	{
		EnemyHpWidget->BindCharacterStat(enemyStat_);
	}
	
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 480.0f, 0.0f);
}

void AADEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AADEnemyCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AADEnemyCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

}

void AADEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	GetCharacterMovement()->MaxWalkSpeed = 300.0f;
}