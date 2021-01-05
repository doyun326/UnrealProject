// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSetting/Portpolio.h"
#include "GameFramework/Actor.h"
#include "WeaponBullet.generated.h"

UCLASS()
class PORTPOLIO_API AWeaponBullet : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeaponBullet();

public:

	UFUNCTION()
		void OnHit(UPrimitiveComponent* _hitComp, AActor* _otherActor, UPrimitiveComponent* _otherComp, FVector _normalImpules, const FHitResult& _hit);

	//FORCELINE 컴파일러의 비용/효율 분석 대신, 프로그래머의 판단을 우선순위를 가지게 해준다. 왠만해선(거의 무조건)inline화 하라고 강요.
	FORCEINLINE class USphereComponent* GetCollisionComp() const
	{
		return collisionComp_;
	}
	FORCEINLINE class UProjectileMovementComponent* GetProjectileMovement() const
	{
		return projectileMovement_;
	}
	
private:
	UPROPERTY(VisibleDefaultsOnly, Category = Bullet)
		class USphereComponent*				collisionComp_;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		class UProjectileMovementComponent*	projectileMovement_;





	UPROPERTY(VisibleAnywhere, Category = Bullet)
		USkeletalMeshComponent*				bulletMesh_;
};
