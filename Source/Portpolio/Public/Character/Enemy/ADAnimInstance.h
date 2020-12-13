// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSetting/Portpolio.h"
#include "Animation/AnimInstance.h"
#include "ADAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PORTPOLIO_API UADAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UADAnimInstance();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AIStat", meta = (AllowPrivateAccess = true))
		float curSpeed_;

};
