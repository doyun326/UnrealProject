// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Portpolio.h"
#include "Animation/AnimInstance.h"
#include "WeaponAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PORTPOLIO_API UWeaponAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UWeaponAnimInstance();

private:
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	FVector testLotation;
	FRotator testRocation;
};
