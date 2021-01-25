// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSetting/Portpolio.h"

#include "Animation/AnimInstance.h"
#include "BossAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PORTPOLIO_API UBossAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UBossAnimInstance();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AIStat", meta = (AllowPrivateAccess = true))
		float	curSpeed_;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AIStat", meta = (AllowPrivateAccess = true))
		bool	isDead_;

};
