// Fill out your copyright notice in the Description page of Project Settings.


#include "WarWeapon.h"
#include "NiagaraFunctionLibrary.h"
#include "Niagara/Public/NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"

#define GUN_MESH_PATH "/Game/My/Asset/Weapon/TestWeapon/Mesh/SK_FPGun.SK_FPGun"
#define FIRE_EFFECT_PATH "/Game/My/Asset/Weapon/WeaponParticle/NS_AR_Muzzleflash_1_INFINITE.NS_AR_Muzzleflash_1_INFINITE"
#define SHOOT_EFFECT_PATH "/Game/sA_ShootingVfxPack/FX/NiagaraSystems/NS_AR_Muzzleflash_2_INFINITE.NS_AR_Muzzleflash_2_INFINITE"

// Sets default values
AWarWeapon::AWarWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	weapon_ = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPON"));
	RootComponent = weapon_;

	//무기 이미지
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> DEFAULT_GUN(TEXT(GUN_MESH_PATH));

	if (DEFAULT_GUN.Succeeded())
	{
		weapon_->SetSkeletalMesh(DEFAULT_GUN.Object);
	}
	weapon_->SetCollisionProfileName(TEXT("No Collison"));

	//발사 이펙트
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> FIRE_EFFECT(TEXT(FIRE_EFFECT_PATH));

	if (FIRE_EFFECT.Succeeded())
	{
		fireEffect_ = FIRE_EFFECT.Object;
	}

	//총 발사 했을때 튕기는 이미지
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> SHOOT_EFFECT(TEXT(SHOOT_EFFECT_PATH));

	if (SHOOT_EFFECT.Succeeded())
	{
		shootEffect_ = SHOOT_EFFECT.Object;
	}

	onEffect_ = nullptr;
	fireStateOld_ = true;
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

void AWarWeapon::PlayFireEffect(bool _newState)
{
	if(_newState && fireStateOld_)
	{
		FName MuzzleSocket("Muzzle");
		muzzleLocation_ = weapon_->GetSocketLocation(MuzzleSocket);
		muzzleRotation_ = weapon_->GetSocketRotation(MuzzleSocket);
		onEffect_ = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, fireEffect_, muzzleLocation_, muzzleRotation_);
		fireStateOld_ = false;
	}
	
	if (!_newState)
	{
		fireStateOld_ = true;
		if (onEffect_ != nullptr)
		{
			onEffect_->Deactivate();
		}
	}
}

void AWarWeapon::PlayShootEffect()
{

}