// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Portpolio.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * �ִϸ��̼� ������ ���� AnimInstance����
 */
UCLASS()
class PORTPOLIO_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPlayerAnimInstance();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
	void	PlayDiveJumpMontage();

public:
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = true))
		float			currentChrSpeed_;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = ActionMotion, meta = (AllowPrivateAccess = true))
		UAnimMontage*	diveMontage_;
};
