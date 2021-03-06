// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Character/Enemy/Boss/CineBossCharacter.h"

#include "Components/SkeletalMeshComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Engine/StaticMesh.h"

#define BOSSMESH_PATH		"/Game/ParagonKhaimera/Characters/Heroes/Khaimera/Meshes/Khaimera.Khaimera"

ACineBossCharacter::ACineBossCharacter()
{
	//Boss Mesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> BOSS_MESH(TEXT(BOSSMESH_PATH));

	if (BOSS_MESH.Succeeded())
	{
		ABLOG(Warning, TEXT("Success : Boss Mesh"));
		GetMesh()->SetSkeletalMesh(BOSS_MESH.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, -95.0f), FRotator(0.0f, -90.0f, 0.0f));
		GetMesh()->SetRelativeScale3D(FVector(1.5f, 1.5f, 1.5f));
	}
}

void ACineBossCharacter::BeginPlay()
{
	Super::BeginPlay();
}

