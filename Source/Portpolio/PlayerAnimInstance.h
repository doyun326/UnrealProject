// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 局聪皋捞记 包府甫 困茄 AnimInstance积己
 */
UCLASS()
class PORTPOLIO_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPlayerAnimInstance();

public:
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = true))
		float currentChrSpeed_;
};
