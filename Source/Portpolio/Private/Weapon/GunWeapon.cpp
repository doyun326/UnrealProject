// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/Weapon/GunWeapon.h"
#include "../Public/Weapon/Bullet.h"

#include "GameFramework/Controller.h"
#include "NiagaraFunctionLibrary.h"
#include "Niagara/Public/NiagaraFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathUtility.h"
#include "DrawDebugHelpers.h"

#define FIRE_EFFECT_PATH	"/Game/My/Asset/Niagara/FireEffect/NS_AR_Muzzleflash_1_ONCE.NS_AR_Muzzleflash_1_ONCE"
#define MUZZLE_PLASH_PATH	"/Game/ParagonWraith/FX/Particles/Abilities/Primary/FX/P_Wraith_Primary_MuzzleFlash.P_Wraith_Primary_MuzzleFlash"

// Sets default values
AGunWeapon::AGunWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	weapon_ = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WEAPON"));
	RootComponent = weapon_;
	weapon_->SetCollisionProfileName(TEXT("No Collison"));

	//�߻� ����Ʈ
	static ConstructorHelpers::FObjectFinder<UParticleSystem> FIRE_EFFECT(TEXT(MUZZLE_PLASH_PATH));

	if (FIRE_EFFECT.Succeeded())
	{
		muzzleEffect_ = FIRE_EFFECT.Object;
		ABLOG(Warning, TEXT("Success : FIRE_EFFECT"));
	}

	//Bullet
	static ConstructorHelpers::FObjectFinder<UClass> BULLET_OBJECT(TEXT("/Game/My/Asset/Weapon/Bullet_BP.Bullet_BP_C"));

	if (BULLET_OBJECT.Succeeded())
	{
		bullet_ = BULLET_OBJECT.Object;
		ABLOG(Warning, TEXT("Success : BULLET_OBJECT"));
	}

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

//���� ����
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

//ź�� �߻� + NiagaraEffect
void AGunWeapon::ShootBullet()
{
	if (bullet_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : WeaponBullet"));
		return;
	}
	ABLOG_S(Error);

	FVector SpawnLocation = muzzleLocation_;
	FRotator SpawnRotation = muzzleRotation_;

	FActorSpawnParameters ActorSpawnParams;
	//ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;//���� ����

	//Bullet Spawn
	ABullet* Bullet = GetWorld()->SpawnActor<ABullet>(bullet_, SpawnLocation, SpawnRotation, ActorSpawnParams);

	//�ҿ��� ����Ʈ
	spawnShootEffect_ = UGameplayStatics::SpawnEmitterAtLocation(this, muzzleEffect_, SpawnLocation, SpawnRotation);

	Bullet->SetFormation(playerAimVector_);
	Bullet->SetDamage(currentDamage_);

	FVector NewVelocity = GetActorRightVector() * 5000.0f;
	Bullet->Velocity = FVector(NewVelocity);
}

void AGunWeapon::SetAimVector(FVector _aimVector)
{
	playerAimVector_ = _aimVector;
}

FVector AGunWeapon::GetAimVector()
{
	return playerAimVector_;
}

void AGunWeapon::SetMuzzleSocketPosition(FVector _muzLoc, FRotator _muzRot)
{
	muzzleLocation_ = _muzLoc;
	muzzleRotation_ = _muzRot;
}

void AGunWeapon::SetPlayerDamage(int32 _newDamage)
{
	currentDamage_ = _newDamage;
}