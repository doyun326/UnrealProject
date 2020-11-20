// Fill out your copyright notice in the Description page of Project Settings.


#include "WarWeapon.h"

// Sets default values
AWarWeapon::AWarWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	weapon_ = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPON"));
	RootComponent = weapon_;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> DEFAULT_GUN(TEXT("/Game/My/Asset/Weapon/TestWeapon/Mesh/SK_FPGun.SK_FPGun"));

	if (DEFAULT_GUN.Succeeded())
	{
		weapon_->SetSkeletalMesh(DEFAULT_GUN.Object);
	}
	weapon_->SetCollisionProfileName(TEXT("No Collison"));
}

// Called when the game starts or when spawned
void AWarWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWarWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

