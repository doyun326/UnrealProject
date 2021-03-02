// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSetting/Portpolio.h"

#include "Animation/AnimInstance.h"
#include "ADAnimInstance.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnAttackHitCheckDelegeate);

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

	void	SetDeadAnim();

	FOnAttackHitCheckDelegeate onAttackHitCheck_;

private:
	UFUNCTION()
		void	AnimNotify_AttackFirEnd();
	UFUNCTION()
		void	AnimNotify_AttackSecEnd();
	UFUNCTION()
		void	AnimNotify_AttackHitCheck();
	UFUNCTION()
		void	AnimNotify_HitEnd();
	UFUNCTION()
		void	AnimNotify_DieEnd();

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AIStat", meta = (AllowPrivateAccess = true))
		float	curSpeed_;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AIStat", meta = (AllowPrivateAccess = true))
		bool	isDead_;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AIStat", meta = (AllowPrivateAccess = true))
		bool	isFirstAttacking_;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AIStat", meta = (AllowPrivateAccess = true))
		bool	isSecondAttacking_;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AIStat", meta = (AllowPrivateAccess = true))
		bool	isInAir_;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AIStat", meta = (AllowPrivateAccess = true))
		bool	isHit_;

	class AADEnemyCharacter* character_;
};
