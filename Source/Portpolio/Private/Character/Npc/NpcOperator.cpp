// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Character/Npc/NpcOperator.h"

#define OPERATORMESH_PATH	"/Game/My/Asset/Character/Operator/Original_Bone/Idle.Idle"

ANpcOperator::ANpcOperator()
{
	PrimaryActorTick.bCanEverTick = true;

	//Operator Mesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> OPER_MESH(TEXT(OPERATORMESH_PATH));

	if (OPER_MESH.Succeeded())
	{
		ABLOG(Warning, TEXT("Success : OPER_MESH"));
		GetMesh()->SetSkeletalMesh(OPER_MESH.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -95.0f), FRotator(0.0f, -90.0f, 0.0f));
		GetMesh()->SetRelativeScale3D(FVector(3.0f, 3.0f, 3.0f));
	}
}

void ANpcOperator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ANpcOperator::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ANpcOperator::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void ANpcOperator::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
}

void ANpcOperator::BeginPlay()
{
	Super::BeginPlay();
}