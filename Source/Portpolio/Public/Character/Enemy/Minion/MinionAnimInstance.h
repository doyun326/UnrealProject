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

	void	SetDeadAnim();

private:
	UFUNCTION()
		void	AnimNotify_AttackFirEnd();
	UFUNCTION()
		void	AnimNotify_AttackSecEnd();
	UFUNCTION()
		void	AnimNotify_AttackThiEnd();
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
		bool	isThirdAttacking_;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AIStat", meta = (AllowPrivateAccess = true))
		bool	isInAir_;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AIStat", meta = (AllowPrivateAccess = true))
		bool	isHit_;

	class AEnemyMinionCharacter* character_;
};
