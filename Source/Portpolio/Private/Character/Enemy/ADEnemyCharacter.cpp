// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Character/Enemy/ADEnemyCharacter.h"
#include "../Public/Character/Enemy/ADAIController.h"

#define TEST_ENEMYMESH_PATH "/Game/My/Asset/Character/Enemy/AD/mutant/mutant.mutant"

AADEnemyCharacter::AADEnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	//AD Class를 Default로 지정
	AIControllerClass = AADAIController::StaticClass();
	//AI컨트롤러에 자동배치
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> AD_ENEMY(TEXT(TEST_ENEMYMESH_PATH));

	if (AD_ENEMY.Succeeded())
	{
		GetMesh()->SetSkeletalMesh((AD_ENEMY.Object));
	}

	GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -95.0f), FRotator(0.0f, -90.0f, 0.0f));
}

void AADEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

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