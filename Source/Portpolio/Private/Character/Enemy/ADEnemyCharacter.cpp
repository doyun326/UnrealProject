// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Character/Enemy/ADEnemyCharacter.h"
#include "../Public/Character/Enemy/ADAIController.h"
#include "../Public/Character/Enemy/ADAnimInstance.h"

#define TEST_ENEMYMESH_PATH "/Game/My/Asset/Character/Enemy/AD/mutant/mutant.mutant"
#define ADANIM_PATH	"/Game/My/Blueprints/Anim/Enemy/ADAnim_BP.ADAnim_BP_C"

AADEnemyCharacter::AADEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	//AD Class�� Default�� ����
	AIControllerClass = AADAIController::StaticClass();
	//AI��Ʈ�ѷ��� �ڵ���ġ
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	//EnemyMesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> AD_ENEMY(TEXT(TEST_ENEMYMESH_PATH));

	if (AD_ENEMY.Succeeded())
	{
		GetMesh()->SetSkeletalMesh((AD_ENEMY.Object));
	}

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -95.0f), FRotator(0.0f, -90.0f, 0.0f));

	//Animation ����
	static ConstructorHelpers::FClassFinder<UADAnimInstance> AD_ANIM(TEXT(ADANIM_PATH));

	if (AD_ANIM.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(AD_ANIM.Class);
	}
}

void AADEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

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