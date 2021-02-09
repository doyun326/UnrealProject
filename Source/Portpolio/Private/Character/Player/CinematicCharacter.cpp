// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Character/Player/CinematicCharacter.h"

#define PLAYERMESH_PATH		"/Game/My/Asset/Character/Player/ODGreen/Meshes/Wraith_ODGreen.Wraith_ODGreen"

ACinematicCharacter::ACinematicCharacter()
{
	PrimaryActorTick.bCanEverTick = true;

	//Character Mesh ¼³Á¤
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> War_Alien(TEXT(PLAYERMESH_PATH));

	if (War_Alien.Succeeded())
	{
		ABLOG(Warning, TEXT("Success : War_Alien"));
		GetMesh()->SetSkeletalMesh(War_Alien.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -95.0f), FRotator(0.0f, -90.0f, 0.0f));
	}
}

void ACinematicCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACinematicCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACinematicCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ACinematicCharacter::BeginPlay()
{
	Super::BeginPlay();
}