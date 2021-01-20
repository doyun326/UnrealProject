// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Weapon/Bullet.h"
#include "../Public/Character/Player/WarPlayerController.h"
#include "../Public/Weapon/GunWeapon.h"

#include "DrawDebugHelpers.h"

ABullet::ABullet()
{
	PrimaryActorTick.bCanEverTick = true;
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

	//ABLOG(Warning, TEXT("%f, %f, %f"), StartTrace.X, StartTrace.Y, StartTrace.Z);
	
	FVector EndTrace = (this->GetActorForwardVector() * 1000.0f) + StartTrace;
	//EndTrace.Z += this->GetActorRotation().Roll;

	FCollisionQueryParams CollisionParams;

	CollisionParams.AddIgnoredActor(this);

	DrawDebugLine(GetWorld(), StartTrace, bulletEndVector_, FColor::Green, false, 0.5, 0, 1);

	//if (GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECC_Destructible, CollisionParams))
	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, bulletEndVector_, ECC_Destructible, CollisionParams))
	{
		if (HitResult.GetActor())
		{
			//DrawDebugSolidBox(GetWorld(), HitResult.ImpactPoint, FVector(10.0f), FColor::Blue, true);

			auto PlayerController = Cast<AWarPlayerController>(playerController_);

			if (PlayerController != nullptr)
			{
				ABLOG(Warning, TEXT("Success : PlayerController"));
			}

			FDamageEvent DamageEvent;
			HitResult.Actor->TakeDamage(50.0f, DamageEvent, PlayerController, this);
			//DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Red);
		}
		Destroy();
	}
	else
	{
		bulletExpiry_ += DeltaTime;
		//DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor(0.f, -bulletExpiry_ * 80.0f, 100.0f));
		//DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Red);
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
