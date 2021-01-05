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

	//FORCELINE �����Ϸ��� ���/ȿ�� �м� ���, ���α׷����� �Ǵ��� �켱������ ������ ���ش�. �ظ��ؼ�(���� ������)inlineȭ �϶�� ����.
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
