// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Portpolio.h"
#include "GameFramework/Actor.h"
#include "NiagaraComponent.h"
#include "WarWeapon.generated.h"

/*
* 무기 장착을 위한 클래스
*/
UCLASS()
class PORTPOLIO_API AWarWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWarWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void	PlayFireEffect(bool _newState);
	void	PlayShootEffect();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
		USkeletalMeshComponent*		weapon_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FX", meta = (AllowPrivateAccess = true))
		class UNiagaraSystem* fireEffect_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "FX", meta = (AllowPrivateAccess = true))
		class UNiagaraSystem* shootEffect_;

private:
	FVector		muzzleLocation_;
	FRotator	muzzleRotation_;
	bool		fireStateOld_;
	UNiagaraComponent* onEffect_;
};
