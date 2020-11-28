// Fill out your copyright notice in the Description page of Project Settings.


#include "WarWeapon.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AWarWeapon::AWarWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	weapon_ = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPON"));
	RootComponent = weapon_;

	//무기 이미지
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> DEFAULT_GUN(TEXT("/Game/My/Asset/Weapon/TestWeapon/Mesh/SK_FPGun.SK_FPGun"));

	if (!DEFAULT_GUN.Succeeded())
	{
		weapon_->SetSkeletalMesh(DEFAULT_GUN.Object);
	}
	else
	{
		ABLOG(Warning, TEXT("DEFAULT_GUN Error!!"))
	}
	weapon_->SetCollisionProfileName(TEXT("No Collison"));

	//무기 발사 파티클
	static ConstructorHelpers::FObjectFinder<UParticleSystem> FIRE_PARTICLE(TEXT("/Game/sA_ShootingVfxPack/FX/NiagaraSystems/NS_AR_Muzzleflash_1_INFINITE.NS_AR_Muzzleflash_1_INFINITE"));

	if (FIRE_PARTICLE.Succeeded())
	{
		fireParticle_ = FIRE_PARTICLE.Object;
	}
	else
	{
		ABLOG(Warning, TEXT("FIRE_PARTICLE Error!!"))
	}
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

