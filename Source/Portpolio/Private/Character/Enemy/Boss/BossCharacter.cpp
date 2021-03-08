// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Character/Enemy/Boss/BossCharacter.h"
#include "../Public/Character/Enemy/Boss/BossAIController.h"
#include "../Public/Character/Enemy/Boss/BossAnimInstance.h"
#include "../Public/Character/Enemy/Boss/BossStatComponent.h"
#include "../Public/GameSetting/WarGameInstance.h"
#include "../Public/UI/BossHPWidget.h"

#include "NiagaraSystem.h"
#include "Niagara/Public/NiagaraFunctionLibrary.h"
#include "Components/WidgetComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"
#include "Engine/StaticMesh.h"

#define BOSSMESH_PATH		"/Game/ParagonKhaimera/Characters/Heroes/Khaimera/Meshes/Khaimera.Khaimera"
#define BOSSANIM_PATH		"/Game/My/Blueprints/Anim/Enemy/Boss/BossAnim_BP.BossAnim_BP_C"
#define BOSSHPWIDGET_PATH	"/Game/My/Blueprints/UI/BossStausBar_UI.BossStausBar_UI_C"
#define DIEEFFECT_PATH		"/Game/My/Asset/Niagara/Flash/BossDieSystem.BossDieSystem"

#define MAX_SPEED		500.0f

ABossCharacter::ABossCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	//AiClass 지정
	AIControllerClass = ABossAIController::StaticClass();
	//AI컨트롤러에 자동배치
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	//Boss Mesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BOSS_MESH(TEXT(BOSSMESH_PATH));

	if (BOSS_MESH.Succeeded())
	{
		ABLOG(Warning, TEXT("Success : Boss Mesh"));
		GetMesh()->SetSkeletalMesh(BOSS_MESH.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -95.0f), FRotator(0.0f, -90.0f, 0.0f));
	}

	//Animation 설정
	static ConstructorHelpers::FClassFinder<UBossAnimInstance> ANIM_PATH(TEXT(BOSSANIM_PATH));

	if (ANIM_PATH.Succeeded())
	{
		ABLOG(Warning, TEXT("Success : BossAnim_Path"));
		GetMesh()->SetAnimInstanceClass(ANIM_PATH.Class);
	}

	//EnemyStat 설정
	enemyStat_ = CreateDefaultSubobject<UBossStatComponent>(TEXT("BossStat"));

	if (enemyStat_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : enemtStat"));
	}

	//HPBar설정
	HPBarWidget_ = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBARWIDGET"));
	static ConstructorHelpers::FClassFinder<UUserWidget> UI_ENEMYHP(TEXT(BOSSHPWIDGET_PATH));

	if (UI_ENEMYHP.Succeeded())
	{
		ABLOG(Warning, TEXT("Success : UI_ENEMYHP"));

		HPBarWidget_->SetWidgetClass(UI_ENEMYHP.Class);
	}

	//Flahs System 설정
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> BOSSDIE_EFFECT(TEXT(DIEEFFECT_PATH));

	if (BOSSDIE_EFFECT.Succeeded())
	{
		ABLOG(Warning, TEXT("Success : FLASH_EFFECT"));
		bossDieEffect_ = BOSSDIE_EFFECT.Object;
	}

	isFirstAttack_ = false;
	isSecondAttack_ = false;
	isThirdAttack_ = false;
	isHiting_ = false;
	isDamageTime_ = true;
}

void ABossCharacter::BeginPlay()
{
	Super::BeginPlay();

	bossAnim_ = Cast<UBossAnimInstance>(GetMesh()->GetAnimInstance());

	if (bossAnim_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : BossEnemyAnim"));
		return;
	}

	if (HPBarWidget_ != nullptr)
	{
		bossHpWidget_ = Cast<UBossHPWidget>(HPBarWidget_->GetUserWidgetObject());

		if (bossHpWidget_ != nullptr)
		{
			ABLOG(Warning, TEXT("Success : bossHPWidget"));
			bossHpWidget_->AddToViewport();
			bossHpWidget_->BindCharacterStat(enemyStat_);
		}
	}

	enemyController_ = Cast<ABossAIController>(GetController());

	if (enemyController_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : EnemyController"));
		return;
	}

	//Delegate Setting
	onFirstAttack_.AddUObject(this, &ABossCharacter::ChangeFirstAttack);
	onSecondAttack_.AddUObject(this, &ABossCharacter::ChangeSecondAttack);
	onThirdAttack_.AddUObject(this, &ABossCharacter::ChangeThirdAttack);
	onHit_.AddUObject(this, &ABossCharacter::ChangeHit);

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 480.0f, 0.0f);

	bossAnim_->onDieEnd_.AddUObject(this, &ABossCharacter::BossDieEffect);

	SetEnemyState(ECharacterState::READY);
}

void ABossCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABossCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void ABossCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (enemyStat_ != nullptr)
	{
		enemyStat_->onHpZero_.AddLambda([this]()->void 
			{
				bossAnim_->SetDeadAnim();
				SetActorEnableCollision(false);
			});
	}
	else
	{
		ABLOG(Error, TEXT("Nullptr : enemyStat"));
		return;
	}
}

void ABossCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	GetCharacterMovement()->MaxWalkSpeed = MAX_SPEED;
}

void ABossCharacter::SetEnemyState(ECharacterState _newState)
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
		/*-------------해당 내용은 추후 Loading으로 옮길것----------------*/
		bossHpWidget_->BindCharacterStat(enemyStat_);
		enemyStat_->SetNewLevel(25);
		/*--------------------------------------------------------------*/

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

float ABossCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
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
		GetWorld()->GetTimerManager().SetTimer(noDamageTimeHandler_, this, &ABossCharacter::NoDamageTime, NODAMAGETIME, false);

		ABLOG(Error, TEXT("Actor : %s TakeDamage : %f"), *GetName(), FinalDamage);

		if (currentState_ == ECharacterState::DEAD)
		{
			//enemyController_->EnemyKill(this);
			//enemyController_->StopAI();
		}

		isDamageTime_ = false;
	}

	return FinalDamage;
}

void ABossCharacter::ChangeFirstAttack(bool _attack)
{
	isFirstAttack_ = _attack;
}

void ABossCharacter::ChangeSecondAttack(bool _attack)
{
	isSecondAttack_ = _attack;
}

void ABossCharacter::ChangeThirdAttack(bool _attack)
{
	isThirdAttack_ = _attack;
}

void ABossCharacter::ChangeHit(bool _hit)
{
	isHiting_ = _hit;
}

bool ABossCharacter::GetFirstAttacking()
{
	return isFirstAttack_;
}

bool ABossCharacter::GetSecondAttacking()
{
	return isSecondAttack_;
}

bool ABossCharacter::GetThirdAttacking()
{
	return isThirdAttack_;
}

bool ABossCharacter::GetIsHiting()
{
	return isHiting_;
}

void ABossCharacter::BossDieEffect()
{
	FName NoneName("none");
	UNiagaraComponent* effect = UNiagaraFunctionLibrary::SpawnSystemAttached(bossDieEffect_, GetMesh(), NoneName, GetMesh()->GetRelativeLocation(), GetMesh()->GetRelativeRotation(), FVector(1.0f, 1.0f, 1.0f), EAttachLocation::KeepRelativeOffset, false, ENCPoolMethod::None);

	GetWorld()->GetTimerManager().SetTimer(effectEndTimeHandler_, this, &ABossCharacter::BossDestroy, 3.0f, false);
}

void ABossCharacter::BossDestroy()
{	
	bossHpWidget_->SetVisibility(ESlateVisibility::Hidden);
	Destroy();
}

void ABossCharacter::NoDamageTime()
{
	isDamageTime_ = true;
}