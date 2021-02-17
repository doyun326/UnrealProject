// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSetting/Portpolio.h"
#include "Animation/AnimInstance.h"

#include "NiagaraComponent.h"
#include "PlayerAnimInstance.generated.h"

DECLARE_DELEGATE_OneParam(FOnChangeSocketDele, FString);
DECLARE_MULTICAST_DELEGATE(FOnFireCheckDelegeate);

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
	
	UFUNCTION()
		void	AnimNotify_FireBullet();

	void	PlayFireMontage();

	FOnFireCheckDelegeate onFireBulletCheck_;
	
	//Test
	FOnChangeSocketDele		OnChangeWalkSocket;
	FOnChangeSocketDele		OnChangeRestSocket;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterState", meta = (AllowPrivateAccess = true))
		float			currentChrSpeed_;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterState", meta = (AllowPrivateAccess = true))
		bool			isFire_;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterState", meta = (AllowPrivateAccess = true))
		bool			isSprint_;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterState", meta = (AllowPrivateAccess = true))
		bool			isWalk_;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterState", meta = (AllowPrivateAccess = true))
		bool			isRest_;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterState", meta = (AllowPrivateAccess = true))
		bool			isInAir_;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CharacterState", meta = (AllowPrivateAccess = true))
		float			lookPitch_;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterState", meta = (AllowPrivateAccess = true))
		bool			isZoom_;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MapInformation", meta = (AllowPrivateAccess = true))
		bool			isLoby_;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "ActionMotion", meta = (AllowPrivateAccess = true))
		UAnimMontage*	walkMontage_;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "ActionMotion", meta = (AllowPrivateAccess = true))
		UAnimMontage*	restMontage_;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Montage", meta = (AllowPrivateAccess = true))
		UAnimMontage*	attackMT_;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = true))
		class USkeletalMeshComponent* characterMesh_;

	class APlayerCharacter* Character_;

	FName		CurrentWeaponName;
};
