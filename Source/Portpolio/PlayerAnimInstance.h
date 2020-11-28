// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Portpolio.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

DECLARE_DELEGATE_OneParam(FOnChangeSocketDele, FString);

/**
 * 局聪皋捞记 包府甫 困茄 AnimInstance积己
 */
UCLASS()
class PORTPOLIO_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPlayerAnimInstance();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
	
	void	PlayDiveJumpMontage();
	void	PlayFireGunMontage();
	void	ChanageWeaponSocket(FName _name);
	
	//Test
	void	PlayTestMontage();
	FOnChangeSocketDele		OnChangeWalkSocket;
	FOnChangeSocketDele		OnChangeRestSocket;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = true))
		float			currentChrSpeed_;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = true))
		bool			isFire_;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character, meta = (AllowPrivateAccess = true))
		bool			isSprint_;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character, meta = (AllowPrivateAccess = true))
		bool			isWalk_;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character, meta = (AllowPrivateAccess = true))
		bool			isRest_;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Character, meta = (AllowPrivateAccess = true))
		bool			isInAir_;



	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = ActionMotion, meta = (AllowPrivateAccess = true))
		UAnimMontage*	diveMontage_;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = ActionMotion, meta = (AllowPrivateAccess = true))
		UAnimMontage*	fireMontage_;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = ActionMotion, meta = (AllowPrivateAccess = true))
		UAnimMontage*	walkMontage_;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = ActionMotion, meta = (AllowPrivateAccess = true))
		UAnimMontage*	restMontage_;

	class APlayerCharacter* Character_;
	FTimerHandle			weaponChangeTimerHandle_;
	FName					CurrentWeaponName;
};
