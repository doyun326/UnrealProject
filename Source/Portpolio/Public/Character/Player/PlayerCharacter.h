// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSetting/Portpolio.h"

#include "Character/BaseCharacter.h"
#include "PlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PORTPOLIO_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;

	void			SetCharacterState(ECharacterState _newState);
	bool			GetIsFire();
	bool			GetSprintBtn();
	float			GetLookPitch();
	void			SetSprintBtn(bool _newState);
	void			SetViewMode(ViewMode _newMode);
	void			OnFire(bool _firBtn); //탄알 발사(RayCast)
	void			WeaponFire();
	void			isInteract();
	void			Interact();
	void			PlayFlashEffect();
	void			PlayLimintClearEffect();
	void			InfinityMode();
	void			LimitLevelUp();
	bool			GetIsWalking();
	bool			GetIsZoom();
	ControlMode		GetCurrentControllMode();
	FVector			GetPlayerLocation();
	FRotator		GetPlayerRotator();
	ECharacterState	GetCharacterState() const;

	//카메라 설정
	UPROPERTY(EditAnywhere, Category = "Camera")
		UCameraComponent*			camera_;
	UPROPERTY(EditAnywhere, Category = "Camera")
		USpringArmComponent*		cameraArm_;
	UPROPERTY(VisibleAnywhere, Category = "Stat")
		class UPlayerStatComponent* playerStat_;

	float		armLengthTo_;

protected:
	virtual void BeginPlay() override;

	ControlMode	currentControlMode_;
	ViewMode	currentViewMode_;

private:
	UPROPERTY()
		class AGunWeapon*			weapon_;
	UPROPERTY()
		class AWarPlayerController*	playerController_;
	UPROPERTY()
		class UPlayerAnimInstance*	playerAnim_;
	UPROPERTY()
		class AWarPlayerState*		warPlayerState_;
	UPROPERTY()
		class UWarGameInstance*		warInstance_;
	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadOnly, Category = "State", meta = (AllowPrivateAccess = true))
		ECharacterState				currentState_;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect", meta = (AllowPrivateAccess = true))
		class UNiagaraSystem*		flashEffect_;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Effect", meta = (AllowPrivateAccess = true))
		class UNiagaraSystem*		limitEffect_;
	UPROPERTY(EditAnywhere, Category = "Camera")
		TSubclassOf<UCameraShake>	myShake_;
		
	bool		isFire_;
	bool		isSprint_;
	bool		isZoomIn_;
	bool		isInteract_;
	float		lookPitch_;
	float		camArmLength_;
	FVector		playerLocation_;
	FRotator	playerRotator_;
	FVector		fireLookPosition_;
	FVector		startPoint_;
	FVector		endPoint_;
	FVector		forwardVector_;
	FName		MuzzleSocket;
	int32		assetIndex_ = 0;
};
