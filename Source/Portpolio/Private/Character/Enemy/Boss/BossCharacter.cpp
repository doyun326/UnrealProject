// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Character/Enemy/Boss/BossCharacter.h"
#include "../Public/Character/Enemy/Boss/BossAIController.h"
#include "../Public/Character/Enemy/Boss/BossAnimInstance.h"

#define BOSSMESH_PATH	"/Game/ParagonKhaimera/Characters/Heroes/Khaimera/Meshes/Khaimera.Khaimera"
#define BOSSANIM_PATH	"/Game/My/Blueprints/Anim/Enemy/Boss/BossAnim_BP.BossAnim_BP_C"

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
		ABLOG(Warning, TEXT("Success : Anim_Path"));
		GetMesh()->SetAnimInstanceClass(ANIM_PATH.Class);
	}
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

}

void ABossCharacter::BeginPlay()
{
	Super::BeginPlay();
}

float ABossCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float FinalDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	return FinalDamage;
}