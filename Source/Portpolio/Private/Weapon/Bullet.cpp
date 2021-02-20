// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Weapon/Bullet.h"
#include "../Public/Character/Player/WarPlayerController.h"
#include "../Public/Weapon/GunWeapon.h"

#include "Kismet/KismetMathLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "Niagara/Public/NiagaraFunctionLibrary.h"
#include "DrawDebugHelpers.h"

#define BULLET_WALL_HIT_PATH "/Game/My/Asset/Niagara/FireEffect/NS_AR_Muzzleflash_2_ONCE.NS_AR_Muzzleflash_2_ONCE"

ABullet::ABullet()
{
	PrimaryActorTick.bCanEverTick = true;

	//≈∫æÀ ¿Ã∆Â∆Æ
	static ConstructorHelpers::FObjectFinder<UNiagaraSystem> BULLET_EFFECT(TEXT(BULLET_WALL_HIT_PATH));

	if (BULLET_EFFECT.Succeeded())
	{
		bulletEffect_ = BULLET_EFFECT.Object;
		ABLOG(Warning, TEXT("Success : BULLET_EFFECT"));
	}

	currentDamage_ = 0;
}

void ABullet::BeginPlay()
{
	Super::BeginPlay();

}

void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult HitResult;
	FVector StartTrace = this->GetActorLocation();
	StartTrace = StartTrace + this->GetActorForwardVector();
	FVector EndTrace = (this->GetActorForwardVector() * 1000.0f) + StartTrace;

	FCollisionQueryParams CollisionParams;

	CollisionParams.AddIgnoredActor(this);

#ifdef DRAW_DEBUGHELPER
	{
		DrawDebugLine(GetWorld(), StartTrace, bulletEndVector_, FColor::Green, false, 0.5, 0, 1);
	}
#endif

	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, bulletEndVector_, ECC_Destructible, CollisionParams))
	{
		FRotator bulletRoatator = UKismetMathLibrary::FindLookAtRotation(this->GetActorLocation(), HitResult.ImpactPoint);
		bulletRoatator.Pitch = bulletRoatator.Pitch * 180.0f;
		onEffect_ = UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, bulletEffect_, HitResult.ImpactPoint, bulletRoatator);

		if (HitResult.GetActor())
		{
			auto PlayerController = Cast<AWarPlayerController>(playerController_);

			if (PlayerController != nullptr)
			{
				ABLOG(Warning, TEXT("Success : PlayerController"));
			}

			FDamageEvent DamageEvent;
			HitResult.Actor->TakeDamage(currentDamage_, DamageEvent, PlayerController, this);

			#ifdef DRAW_DEBUGHELPER
			{
				ABLOG(Warning, TEXT("Hit!!!"));
				DrawDebugSolidBox(GetWorld(), HitResult.ImpactPoint, FVector(10.0f), FColor::Blue, true);
				//DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Red);
			}
			#endif
		}
		Destroy();
	}
	else
	{
		bulletExpiry_ += DeltaTime;
#ifdef DRAW_DEBUGHELPER
		{
			//DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor(0.f, -bulletExpiry_ * 80.0f, 100.0f));
			//DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Red);
		}
#endif
		SetActorLocation(EndTrace);
		Velocity += FVector(0.f, 0.0f, -200.0f) * DeltaTime;
	}

	if (bulletExpiry_ > 0.3)
	{
		Destroy();
	}
}

void ABullet::SetFormation(FVector _playerAimVector)
{
	bulletEndVector_ = _playerAimVector;
}

void ABullet::SetDamage(int32 _newDamage)
{
	currentDamage_ = _newDamage;
}
