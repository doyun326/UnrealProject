// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "NpcOperatorAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class PORTPOLIO_API UNpcOperatorAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UNpcOperatorAnimInstance();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

private:
};
