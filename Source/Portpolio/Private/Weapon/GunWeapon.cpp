// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/Weapon/GunWeapon.h"
#include "../Public/Weapon/Bullet.h"

#include "GameFramework/Controller.h"
#include "NiagaraFunctionLibrary.h"
#include "Niagara/Public/NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathUtility.h"

#define GUN_MESH_PATH "/Game/My/Asset/Weapon/TestWeapon/Mesh/SK_FPGun.SK_FPGun"
#define FIRE_EFFECT_PATH "/Game/My/Asset/Niagara/FireEffect/NS_AR_Muzzleflash_1_ONCE.NS_AR_Muzzleflash_1_ONCE"
#define SHOOT_EFFECT_PATH "/Game/sA_ShootingVfxPack/FX/NiagaraSystems/NS_AR_Muzzleflash_2_INFINITE.NS_AR_Muzzleflash_2_INFINITE"

// Sets default values
AGunWeapon::AGunWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	weapon_ = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPON"));
	RootComponent = weapon_;

	//무기 이미지
	/*static ConstructorHelpers::FObjectFinder<USkeletalMesh> DEFAULT_GUN(TEXT(GUN_MESH_PATH));

	if (DEFAULT_GUN.Succeeded())
	{
		weapon_->SetSkeletalMesh(DEFAULT_GUN.Object);
		ABLOG(Warning, TEXT("Success : DEFAULT_GUN"));
	}
	weapon_->SetCollisionProfileName(TEXT("No Collison"));*/

	//발사 이펙트
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> FIRE_EFFECT(TEXT(FIRE_EFFECT_PATH));

	if (FIRE_EFFECT.Succeeded())
	{
		fireEffect_ = FIRE_EFFECT.Object;
		ABLOG(Warning, TEXT("Success : FIRE_EFFECT"));
	}

	//총 발사 했을때 튕기는 이미지
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> SHOOT_EFFECT(TEXT(SHOOT_EFFECT_PATH));

	if (SHOOT_EFFECT.Succeeded())
	{
		shootEffect_ = SHOOT_EFFECT.Object;
		ABLOG(Warning, TEXT("Success : SHOOT_EFFECT"));
	}

	//Bullet
	static ConstructorHelpers::FObjectFinder<UClass> BULLET_OBJECT(TEXT("/Game/My/Asset/Weapon/Bullet_BP.Bullet_BP_C"));

	if (BULLET_OBJECT.Succeeded())
	{
		bullet_ = BULLET_OBJECT.Object;
		ABLOG(Warning, TEXT("Success : BULLET_OBJECT"));
	}

	onEffect_ = nullptr;
	fireStateOld_ = true;
}

// Called when the game starts or when spawned
void AGunWeapon::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AGunWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

//실제 공격
void AGunWeapon::OnFire(bool _fire)
{
	UWorld* const World = GetWorld();

	if (World == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr: World"));
		return;
	}

	if (_fire)
	{
		if (!isShooting_)
		{
			isShooting_ = true;
			World->GetTimerManager().SetTimer(shootDelayTimerHandle_, this, &AGunWeapon::ShootBullet, 0.08f, true);
		}
	}
	else
	{
		if (isShooting_)
		{
			isShooting_ = false;
			GetWorld()->GetTimerManager().ClearTimer(shootDelayTimerHandle_);
		}
	}
}

void AGunWeapon::ShootBullet()
{
	if (bullet_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : weaponBullet"));
		return;
	}

	//FName MuzzleSocket("Muzzle");
	FName MuzzleSocket("Muzzle_01");
	FVector SpawnLocation = weapon_->GetSocketLocation(MuzzleSocket);
	FRotator SpawnRotation = weapon_->GetSocketRotation(MuzzleSocket);

	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;//관통 여부

	//Bullet Spawn
	ABullet* Bullet = GetWorld()->SpawnActor<ABullet>(bullet_, SpawnLocation, SpawnRotation, ActorSpawnParams);

	//소염기 이펙트
	onEffect_ = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, fireEffect_, SpawnLocation, SpawnRotation);

	Bullet->SetFormation(playerAimVector_);
	FVector NewVelocity = GetActorRightVector() * 5000.0f;
	Bullet->Velocity = FVector(NewVelocity);
}

//탄알 벽에 충돌 시 이펙트
void AGunWeapon::PlayShootEffect(FVector _newLocation)
{
	muzzleRotation_.Pitch = muzzleRotation_.Pitch * 90.0f;

	FRotator test1;
	test1.Pitch = 180.0f;
	test1.Yaw = 0.0f;
	test1.Roll = 0.0f;

	spawnShootEffect_ = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, shootEffect_, _newLocation, test1);
}

void AGunWeapon::SetAimVector(FVector _aimVector)
{
	playerAimVector_ = _aimVector;
}

FVector AGunWeapon::GetAimVector()
{
	return playerAimVector_;
}