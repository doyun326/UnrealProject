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
}

void AEnemyMinionCharacter::BeginPlay()
{
	Super::BeginPlay();

	minionAnim_ = Cast<UMinionAnimInstance>(GetMesh()->GetAnimInstance());
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

}

void AEnemyMinionCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

float AEnemyMinionCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	return FinalDamage;
}

void AEnemyMinionCharacter::EnemyDestroy()
{
	Destroy();
}