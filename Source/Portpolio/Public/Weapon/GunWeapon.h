// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSetting/Portpolio.h"

#include "GameFramework/Actor.h"
#include "NiagaraComponent.h"
#include "GunWeapon.generated.h"

/*
* ���� ������ ���� Ŭ����
*/
UCLASS()
class PORTPOLIO_API AGunWeapon : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGunWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void	ShootBullet();

	void	OnFire(bool _fire);
	void	SetAimVector(FVector _aimVector);
	void	SetMuzzleSocketPosition(FVector _muzLoc, FRotator _muzRot);
	void	FireShootGun();
	FVector	GetAimVector();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
		USkeletalMeshComponent*	weapon_;
	
	UPROPERTY(EditDefaultsOnly, Category = "Bulle")
		TSubclassOf<class ABullet>	bullet_;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FX", meta = (AllowPrivateAccess = true))
		class UNiagaraSystem* fireEffect_;

	bool		rayHit_;
	bool		isShooting_;
	bool		fireStateOld_;

	FVector		muzzleLocation_;
	FRotator	muzzleRotation_;
	FVector		playerAimVector_;
	
	FTimerHandle		shootDelayTimerHandle_;

	UNiagaraComponent* onEffect_;
	UNiagaraComponent* spawnShootEffect_;
};
