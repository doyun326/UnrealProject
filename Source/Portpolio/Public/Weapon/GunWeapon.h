// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSetting/Portpolio.h"
#include "GameFramework/Actor.h"
#include "NiagaraComponent.h"
#include "GunWeapon.generated.h"

/*
* 무기 장착을 위한 클래스
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
		void	RayCastHit();

	void	OnFire(bool _fire);
	void	PlayFireEffect(bool _newState);
	void	PlayShootEffect(FVector _newLocation);
	void	SetPlayerCamInfo(FVector _cameraLoc, FVector _forwardVec, FVector _playerLoc, float _armLength);
	FRotator	GetShootRot();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
		USkeletalMeshComponent* weapon_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FX", meta = (AllowPrivateAccess = true))
		class UNiagaraSystem* fireEffect_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FX", meta = (AllowPrivateAccess = true))
		class UNiagaraSystem* shootEffect_;

private:
	FVector		startPoint_;
	FVector		forwardVector_;
	FVector		endPoint_;
	FRotator	shootRot_;
	FVector		playerLoc_;

	float		camArmLength_;
	bool		rayHit_;
	bool		isShooting_;

	FVector		muzzleLocation_;
	FRotator	muzzleRotation_;
	bool		fireStateOld_;

	FTimerHandle		shootDelayTimerHandle_;

	UNiagaraComponent* onEffect_;
	UNiagaraComponent* spawnShootEffect_;
};
