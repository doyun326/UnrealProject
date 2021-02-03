// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Character/Enemy/Minion/EnemyMinionCharacter.h"
#include "../Public/Character/Enemy/Minion/MinionAIController.h"
#include "../Public/Character/Enemy/Minion/MinionAnimInstance.h"
#include "../Public/Character/Enemy/Minion/MinionEnemyStatComponent.h"
#include "../Public/UI/MinionHPWidget.h"

#include "Components/WidgetComponent.h"

#define MINIONMESH_PATH			"/Game/ParagonMinions/Characters/Minions/Dusk_Minions/Meshes/Minion_Lane_Super_Dusk.Minion_Lane_Super_Dusk"
#define MINIONANIM_PATH			"/Game/My/Blueprints/Anim/Enemy/MinionAnim_BP.MinionAnim_BP_C"
#define ADENEMY_WIDGET_PATH		"/Game/My/Blueprints/UI/MinionHpBar_UI.MinionHpBar_UI_C"

#define MAX_SPEED		500.0f

AEnemyMinionCharacter::AEnemyMinionCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	//AIClass 지정
	AIControllerClass = AMinionAIController::StaticClass();
	//AI컨트롤러에 자동배치
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	//MinionMesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MINION_MESH(TEXT(MINIONMESH_PATH));

	if (MINION_MESH.Succeeded())
	{
		ABLOG(Warning, TEXT("Success : MINION_MESH"));
		GetMesh()->SetSkeletalMesh(MINION_MESH.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -95.0f), FRotator(0.0f, -90.0f, 0.0f));
	}

	//Animation 설정
	static ConstructorHelpers::FClassFinder<UMinionAnimInstance> ANIM_PATH(TEXT(MINIONANIM_PATH));

	if (ANIM_PATH.Succeeded())
	{
		ABLOG(Warning, TEXT("Success : MinionAnim_Path"));
		GetMesh()->SetAnimInstanceClass(ANIM_PATH.Class);
	}

	//EnemyStat 설정
	enemyStat_ = CreateDefaultSubobject<UMinionEnemyStatComponent>(TEXT("ADENEMYSTAT"));

	if (enemyStat_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : enemtStat"));
	}

	//HPBar설정
	HPBarWidget_ = CreateDefaultSubobject<UWidgetComponent>(TEXT("HPBARWIDGET"));
	HPBarWidget_->SetupAttachment(GetMesh());
	HPBarWidget_->SetRelativeLocation(FVector(0.0f, 0.0f, 250.0f));
	HPBarWidget_->SetWidgetSpace(EWidgetSpace::Screen);

	static ConstructorHelpers::FClassFinder<UUserWidget> UI_ENEMYHP(TEXT(ADENEMY_WIDGET_PATH));

	if (UI_ENEMYHP.Succeeded())
	{
		ABLOG(Warning, TEXT("Success : UI_ENEMYHP"));

		HPBarWidget_->SetWidgetClass(UI_ENEMYHP.Class);
		HPBarWidget_->SetDrawSize(FVector2D(120.0f, 50.0f));
	}

	isFirstAttack_ = false;
	isSecondAttack_ = false;
	isThirdAttack_ = false;
	isHiting_ = false;
}

void AEnemyMinionCharacter::BeginPlay()
{
	Super::BeginPlay();

	minionAnim_ = Cast<UMinionAnimInstance>(GetMesh()->GetAnimInstance());

	if (minionAnim_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : minionAnim"));
		return;
	}

	//HPBar 연결(4.21ver 이 후, PostInitializeComponents()가 아닌 Widget초기화를 BeginPlay에서 한다.)
	if (HPBarWidget_ != nullptr)
	{
		minionHpWidget_ = Cast<UMinionHPWidget>(HPBarWidget_->GetUserWidgetObject());

		if (minionHpWidget_ == nullptr)
		{
			ABLOG(Error, TEXT("Nullptr : minionHpWidget_"))
			return;
		}
		minionHpWidget_->BindCharacterStat(enemyStat_);
	}

	//Delegate Setting
	onFirstAttack_.AddUObject(this, &AEnemyMinionCharacter::ChangeFirstAttack);
	onSecondAttack_.AddUObject(this, &AEnemyMinionCharacter::ChangeSecondAttack);
	onThirdAttack_.AddUObject(this, &AEnemyMinionCharacter::ChangeThirdAttack);
	onHit_.AddUObject(this, &AEnemyMinionCharacter::ChangeHit);

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 480.0f, 0.0f);
}

void AEnemyMinionCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyMinionCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemyMinionCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	if (enemyStat_ != nullptr)
	{
		enemyStat_->onHpZero_.AddLambda([this]()->void
			{
				ABLOG(Warning, TEXT("Character Die"));
				//minionAnim_->SetDeadAnim();
				SetActorEnableCollision(false);
			});
	}
	else
	{
		ABLOG(Error, TEXT("Nullptr : enemyStat"));
		return;
	}
}

void AEnemyMinionCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	GetCharacterMovement()->MaxWalkSpeed = MAX_SPEED;
}

float AEnemyMinionCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	ABLOG(Warning, TEXT("Actor : %s TakeDamage : %f"), *GetName(), FinalDamage);
	if (enemyStat_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : enemtStat_"));
		return 0.0f;
	}

	enemyStat_->SetDamage(FinalDamage);
	isHiting_ = true;

	return FinalDamage;
}

void AEnemyMinionCharacter::ChangeFirstAttack(bool _attack)
{
	isFirstAttack_ = _attack;
}

void AEnemyMinionCharacter::ChangeSecondAttack(bool _attack)
{
	isSecondAttack_ = _attack;
}

void AEnemyMinionCharacter::ChangeThirdAttack(bool _attack)
{
	isThirdAttack_ = _attack;
}

void AEnemyMinionCharacter::ChangeHit(bool _hit)
{
	isHiting_ = _hit;	
}

bool AEnemyMinionCharacter::GetFirstAttacking()
{
	return isFirstAttack_;
}

bool AEnemyMinionCharacter::GetSecondAttacking()
{
	return isSecondAttack_;
}

bool AEnemyMinionCharacter::GetThirdAttacking()
{
	return isThirdAttack_;
}
bool AEnemyMinionCharacter::GetIsHiting()
{
	return isHiting_;
}

void AEnemyMinionCharacter::EnemyDestroy()
{
	Destroy();
}