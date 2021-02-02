// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Character/Enemy/Minion/EnemyMinionCharacter.h"
#include "../Public/Character/Enemy/Minion/MinionAIController.h"
#include "../Public/Character/Enemy/Minion/MinionAnimInstance.h"

#define MINIONMESH_PATH "/Game/ParagonMinions/Characters/Minions/Dusk_Minions/Meshes/Minion_Lane_Super_Dusk.Minion_Lane_Super_Dusk"
#define MINIONANIM_PATH "/Game/My/Blueprints/Anim/Enemy/MinionAnim_BP.MinionAnim_BP_C"

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

void AEnemyMinionCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AEnemyMinionCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AEnemyMinionCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	GetCharacterMovement()->MaxWalkSpeed = MAX_SPEED;

}

void AEnemyMinionCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float AEnemyMinionCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

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