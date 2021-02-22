// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Character/Enemy/ADEnemyCharacter.h"
#include "../Public/Character/Enemy/ADAIController.h"
#include "../Public/Character/Enemy/ADAnimInstance.h"
#include "../Public/Character/Enemy/ADEnemyStatComponent.h"
#include "../Public/UI/EnemyHPWidget.h"

#include "Components/WidgetComponent.h"

#define ENEMYMESH_PATH			"/Game/My/Asset/Character/Enemy/AD/mutant/mutant.mutant"
#define ADANIM_PATH				"/Game/My/Blueprints/Anim/Enemy/ADAnim_BP.ADAnim_BP_C"
#define ADENEMY_WIDGET_PATH		"/Game/My/Blueprints/UI/EnemyHpBar_UI.EnemyHpBar_UI_C"

#define MAX_SPEED		300.0f

AADEnemyCharacter::AADEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	//AD Class를 Default로 지정
	AIControllerClass = AADAIController::StaticClass();
	//AI컨트롤러에 자동배치
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	//EnemyMesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> AD_ENEMY(TEXT(ENEMYMESH_PATH));

	if (AD_ENEMY.Succeeded())
	{
		ABLOG(Warning, TEXT("Success : AD_ENEMY"));
		GetMesh()->SetSkeletalMesh((AD_ENEMY.Object));
		GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -95.0f), FRotator(0.0f, -90.0f, 0.0f));
	}

	//Animation 설정
	static ConstructorHelpers::FClassFinder<UADAnimInstance> AD_ANIM(TEXT(ADANIM_PATH));

	if (AD_ANIM.Succeeded())
	{
		ABLOG(Warning, TEXT("Success : AD_ANIM"));
		GetMesh()->SetAnimInstanceClass(AD_ANIM.Class);
	}

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -95.0f), FRotator(0.0f, -90.0f, 0.0f));

	//EnemyStat 설정
	enemyStat_ = CreateDefaultSubobject<UADEnemyStatComponent>(TEXT("ADENEMYSTAT"));

	if (enemyStat_ ==  nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : enemtStat"));
	}

	//HPBar설정
	HPBarWidget_ = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBARWIDGET"));
	HPBarWidget_->SetupAttachment(GetMesh());
	HPBarWidget_->SetRelativeLocation(FVector(0.0f, 0.0f, 200.0f));
	HPBarWidget_->SetWidgetSpace(EWidgetSpace::Screen);

	static ConstructorHelpers::FClassFinder<UUserWidget> UI_ENEMYHP(TEXT(ADENEMY_WIDGET_PATH));

	if (UI_ENEMYHP.Succeeded())
	{
		ABLOG(Warning, TEXT("Success : UI_ENEMYHP"));

		HPBarWidget_->SetWidgetClass(UI_ENEMYHP.Class);
		HPBarWidget_->SetDrawSize(FVector2D(120.0f, 50.0f));
	}
} 

void AADEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	ADAnim_ = Cast<UADAnimInstance>(GetMesh()->GetAnimInstance());
	enemyController_ = Cast<AADAIController>(GetController());

	if (ADAnim_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : ADEnemyAnim"));
		return;
	}

	if (enemyController_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : enemyController"));
		return;
	}

	//HPBar 연결(4.21ver 이 후, PostInitializeComponents()가 아닌 Widget초기화를 BeginPlay에서 한다.)
	if (HPBarWidget_ != nullptr)
	{
		EnemyHpWidget_ = Cast<UEnemyHPWidget>(HPBarWidget_->GetUserWidgetObject());

		if (EnemyHpWidget_ != nullptr)
		{
			EnemyHpWidget_->BindCharacterStat(enemyStat_);
		}
	}
	
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 480.0f, 0.0f);

	SetEnemyState(ECharacterState::READY);
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

	if (enemyStat_ != nullptr)
	{
		enemyStat_->onHpZero_.AddLambda([this]()->void 
			{
				ABLOG(Warning, TEXT("Character Die"));
				ADAnim_->SetDeadAnim();
				SetActorEnableCollision(false);
			});
	}
	else
	{
		ABLOG(Error, TEXT("Nullptr : enemyStat"));
		return;
	}
}

void AADEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	GetCharacterMovement()->MaxWalkSpeed = MAX_SPEED;
}

void AADEnemyCharacter::SetEnemyState(ECharacterState _newState)
{
	currentState_ = _newState;

	if (enemyStat_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : enemyStat"));
		return;
	}

	if (enemyController_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : enemyController"));
		return;
	}

	switch (currentState_)
	{
	case ECharacterState::LOADING:
	{
		break;
	}

	case ECharacterState::READY:
	{
		enemyStat_->onHpZero_.AddLambda([this]() -> void
			{
				SetEnemyState(ECharacterState::DEAD);
			});
		break;
	}

	case ECharacterState::DEAD:
	{
		SetActorEnableCollision(false);
		GetMesh()->SetHiddenInGame(false);
		break;
	}
	}
}

ECharacterState	AADEnemyCharacter::GetEnemyState() const
{
	return currentState_;
}

float AADEnemyCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	enemyStat_->SetDamage(FinalDamage);
	ABLOG(Error, TEXT("Actor : %s TakeDamage : %f"), *GetName(), FinalDamage);

	if (enemyStat_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : enemtStat_"));
		return 0.0f;
	}

	if (currentState_ == ECharacterState::DEAD)
	{
		if (enemyController_ == nullptr)
		{
			ABLOG(Error, TEXT("Nullptr : enemyController_"));
			return 0.0f;
		}
		enemyController_->EnemyKill(this);
	}
	return FinalDamage;
}

void AADEnemyCharacter::EnemyDestroy()
{
	Destroy();
}

int32 AADEnemyCharacter::GetExp() const
{
	return enemyStat_->GetDropExp();
}