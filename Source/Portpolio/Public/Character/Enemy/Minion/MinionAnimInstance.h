// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSetting/Portpolio.h"

#include "Animation/AnimInstance.h"
#include "MinionAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PORTPOLIO_API UMinionAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UMinionAnimInstance();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

protected:


private:

	
};
