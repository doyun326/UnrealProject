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
#define FIRE_EFFECT_PATH "/Game/My/Asset/Niagara/FireEffect/NS_AR_Muzzleflash_1_INFINITE.NS_AR_Muzzleflash_1_INFINITE"
#define SHOOT_EFFECT_PATH "/Game/sA_ShootingVfxPack/FX/NiagaraSystems/NS_AR_Muzzleflash_2_INFINITE.NS_AR_Muzzleflash_2_INFINITE"

// Sets default values
AGunWeapon::AGunWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	weapon_ = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPON"));
	RootComponent = weapon_;

	//무기 이미지
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> DEFAULT_GUN(TEXT(GUN_MESH_PATH));

	if (DEFAULT_GUN.Succeeded())
	{
		weapon_->SetSkeletalMesh(DEFAULT_GUN.Object);
		ABLOG(Warning, TEXT("Success : DEFAULT_GUN"));
	}
	weapon_->SetCollisionProfileName(TEXT("No Collison"));

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
		ABLOG(Error, TEXT("NULLPTR: World"));
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
			PlayFireEffect(false);
			GetWorld()->GetTimerManager().ClearTimer(shootDelayTimerHandle_);
		}
	}

	/*Draw rayCast debug Line START*/
	//DrawDebugLine(GetWorld(), startPoint_, endPoint_, FColor::Red, false, 1, 0, 1);
	/*Draw rayCast debug Line END*/
}

void AGunWeapon::ShootBullet()
{
	if (bullet_ == nullptr)
	{
		ABLOG(Error, TEXT("NULLPTR : weaponBullet"));
	}
	else
	{
		FName MuzzleSocket("Muzzle");
		FVector SpawnLocation = weapon_->GetSocketLocation(MuzzleSocket);
		FRotator SpawnRotation = weapon_->GetSocketRotation(MuzzleSocket);

		FActorSpawnParameters ActorSpawnParams;
		ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;//관통 여부

		ABullet* Bullet = GetWorld()->SpawnActor<ABullet>(bullet_, SpawnLocation, SpawnRotation, ActorSpawnParams);
		Bullet->SetFormation();
		FVector NewVelocity = GetActorRightVector() * 5000.0f;
		Bullet->Velocity = FVector(NewVelocity);
		ABLOG(Warning, TEXT("Spawn Bullet"));
	}

	PlayFireEffect(true);
}

//소염기 이펙트
void AGunWeapon::PlayFireEffect(bool _newState)
{
	if (_newState && fireStateOld_)
	{
		FName MuzzleSocket("Muzzle");
		muzzleLocation_ = weapon_->GetSocketLocation(MuzzleSocket);
		muzzleRotation_ = weapon_->GetSocketRotation(MuzzleSocket);
		muzzleRotation_.Pitch = muzzleRotation_.Pitch * 90.0f;
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

void AGunWeapon::SetPlayerCamInfo(FVector _cameraLoc, FVector _forwardVec, FVector _playerLoc, float _armLength)
{
	startPoint_ = _cameraLoc;
	forwardVector_ = _forwardVec;
	camArmLength_ = _armLength;
	playerLoc_ = _playerLoc;
}

FRotator AGunWeapon::GetShootRot()
{
	return shootRot_;
}