// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Weapon/Bullet.h"

#include "DrawDebugHelpers.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FHitResult HitResult;
	FVector StartTrace = this->GetActorLocation();
	
	FVector EndTrace = (this->GetActorForwardVector() * 1000.0f) + StartTrace;
	//EndTrace.Z += this->GetActorRotation().Roll;

	FCollisionQueryParams CollisionParams;

	CollisionParams.AddIgnoredActor(this);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartTrace, EndTrace, ECC_Destructible, CollisionParams))
	{
		if (HitResult.GetActor())
		{
			DrawDebugSolidBox(GetWorld(), HitResult.ImpactPoint, FVector(10.0f), FColor::Blue, true);
		}
		ABLOG(Warning, TEXT("shot and Actor Hit"));
		Destroy();
	}
	else
	{
		bulletExpiry_ += DeltaTime;
		//DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor(0.f, -bulletExpiry_ * 80.0f, 100.0f));
		DrawDebugLine(GetWorld(), StartTrace, EndTrace, FColor::Red);
		SetActorLocation(EndTrace);
		Velocity += FVector(0.f, 0.0f, -200.0f) * DeltaTime;
	}

	if (bulletExpiry_ > 0.1)
	{
		Destroy();
	}
}

void ABullet::SetFormation()
{

}
