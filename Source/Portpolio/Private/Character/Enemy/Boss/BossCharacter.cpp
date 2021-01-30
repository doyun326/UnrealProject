// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Character/Enemy/Boss/BossCharacter.h"
#include "../Public/Character/Enemy/Boss/BossAIController.h"
#include "../Public/Character/Enemy/Boss/BossAnimInstance.h"

#define BOSSMESH_PATH	"/Game/ParagonKhaimera/Characters/Heroes/Khaimera/Meshes/Khaimera.Khaimera"
#define BOSSANIM_PATH	"/Game/My/Blueprints/Anim/Enemy/Boss/BossAnim_BP.BossAnim_BP_C"

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

	isFirstAttack_ = false;
	isSecondAttack_ = false;
	isThirdAttack_ = false;
	isHiting_ = false;
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

	//Delegate Setting
	onFirstAttack_.AddUObject(this, &ABossCharacter::ChangeFirstAttack);
	onSecondAttack_.AddUObject(this, &ABossCharacter::ChangeSecondAttack);
	onThirdAttack_.AddUObject(this, &ABossCharacter::ChangeThirdAttack);
	onHit_.AddUObject(this, &ABossCharacter::ChangeHit);

	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 480.0f, 0.0f);
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
}

void ABossCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	GetCharacterMovement()->MaxWalkSpeed = MAX_SPEED;
}

float ABossCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	isHiting_ = true;

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