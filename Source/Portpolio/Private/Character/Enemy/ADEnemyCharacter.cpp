// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Character/Enemy/ADEnemyCharacter.h"
#include "../Public/Character/Enemy/ADAIController.h"
#include "../Public/Character/Enemy/ADAnimInstance.h"
#include "../Public/Character/Enemy/ADEnemyStatComponent.h"
#include "../Public/GameSetting/WarGameInstance.h"
#include "../Public/UI/EnemyHPWidget.h"

#include "Components/WidgetComponent.h"
#include "DrawDebugHelpers.h"

#define ENEMYMESH_PATH			"/Game/My/Asset/Character/Enemy/AD/mutant/mutant.mutant"
#define ADANIM_PATH				"/Game/My/Blueprints/Anim/Enemy/ADAnim_BP.ADAnim_BP_C"
#define ADENEMY_WIDGET_PATH		"/Game/My/Blueprints/UI/EnemyHpBar_UI.EnemyHpBar_UI_C"

#define MAX_SPEED		800.0f

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
	GetMesh()->SetRelativeScale3D(FVector(1.5f, 1.5f, 1.5f));

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
	isHiting_ = false;
	isDamageTime_ = true;
} 

void AADEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	ADAnim_ = Cast<UADAnimInstance>(GetMesh()->GetAnimInstance());
	enemyController_ = Cast<AADAIController>(GetController());
	warInstance_ = Cast<UWarGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));

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

	if (warInstance_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : warInstance"));
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

	//Delegate Setting
	onFirstAttack_.AddUObject(this, &AADEnemyCharacter::ChangeFirstAttack);
	onSecondAttack_.AddUObject(this, &AADEnemyCharacter::ChangeSecondAttack);
	onHit_.AddUObject(this, &AADEnemyCharacter::ChangeHit);
	ADAnim_->onAttackHitCheck_.AddUObject(this, &AADEnemyCharacter::AttackCheck);
	warInstance_->onChangeSeqence.AddUObject(this, &AADEnemyCharacter::EndSequence);
	
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 480.0f, 0.0f);
	

	SetEnemyState(ECharacterState::LOADING);
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

void AADEnemyCharacter::AttackCheck()
{
	FHitResult HitResult;
	FCollisionQueryParams Params(NAME_None, false, this);

	bool bResult = GetWorld()->SweepSingleByChannel(
		HitResult,
		GetActorLocation(),
		GetActorLocation() + GetActorForwardVector() * 200.0f,
		FQuat::Identity,
		ECollisionChannel::ECC_GameTraceChannel2,
		FCollisionShape::MakeSphere(50.0f),
		Params);

	FVector TraceVec = GetActorForwardVector() * 50.0f;
	FVector Center = GetActorLocation() + TraceVec * 0.5f;
	float HalfHeight = 50.0f * 0.5f + 50.0f;
	FQuat CapsuleRot = FRotationMatrix::MakeFromZ(TraceVec).ToQuat();
	FColor DrawColor = bResult ? FColor::Green : FColor::Red;
	float DebugLifeTime = 5.0f;

	DrawDebugCapsule(
		GetWorld(),
		Center,
		HalfHeight,
		50.0f,
		CapsuleRot,
		DrawColor,
		false,
		DebugLifeTime
	);
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
		EnemyHpWidget_->SetVisibility(ESlateVisibility::Hidden);
		break;
	}

	case ECharacterState::READY:
	{
		EnemyHpWidget_->SetVisibility(ESlateVisibility::Visible);
		enemyController_->SetIsHit(isHiting_);
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

	if (enemyController_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : enemyController_"));
		return 0.0f;
	}

	if (enemyStat_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : enemtStat_"));
		return 0.0f;
	}

	if (isDamageTime_)
	{
		enemyStat_->SetDamage(FinalDamage);
		isHiting_ = true;
		enemyController_->SetIsHit(isHiting_);
		GetWorld()->GetTimerManager().SetTimer(noDamageTimeHandler_, this, &AADEnemyCharacter::NoDamageTime, NODAMAGETIME, false);

		ABLOG(Error, TEXT("Actor : %s TakeDamage : %f"), *GetName(), FinalDamage);

		if (currentState_ == ECharacterState::DEAD)
		{
			enemyController_->EnemyKill(this);
			enemyController_->StopAI();
		}
		isDamageTime_ = false;
	}
	else
	{
		FinalDamage = 0.0f;
	}

	return FinalDamage;
}

void AADEnemyCharacter::NoDamageTime()
{
	isDamageTime_ = true;
}

void AADEnemyCharacter::ChangeFirstAttack(bool _attack)
{
	isFirstAttack_ = _attack;
}

void AADEnemyCharacter::ChangeSecondAttack(bool _attack)
{
	isSecondAttack_ = _attack;
}

void AADEnemyCharacter::ChangeHit(bool _hit)
{
	isHiting_ = _hit;
}

bool AADEnemyCharacter::GetFirstAttacking()
{
	return isFirstAttack_;
}

bool AADEnemyCharacter::GetSecondAttacking()
{
	return isSecondAttack_;
}

bool AADEnemyCharacter::GetIsHiting()
{
	return isHiting_;
}

void AADEnemyCharacter::EnemyDestroy()
{
	Destroy();
}

int32 AADEnemyCharacter::GetExp() const
{
	return enemyStat_->GetDropExp();
}

void AADEnemyCharacter::EndSequence(bool _isPlay)
{
	if (!_isPlay && UGameplayStatics::GetCurrentLevelName(GetWorld()) == "Stage_01")
	{
		SetEnemyState(ECharacterState::READY);
	}
}