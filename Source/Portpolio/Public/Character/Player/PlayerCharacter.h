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
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	ControlMode	currentControlMode_;
	ViewMode	currentViewMode_;

public:
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;

	void			PlayMontageDiveJump();
	bool			GetIsFire();
	bool			GetSprintBtn();
	ControlMode		GetCurrentControllMode();
	FVector			GetPlayerLocation();
	FRotator		GetPlayerRotator();
	float			GetLookClampPitch();
	void			SetSprintBtn(bool _newState);
	void			SetWeaponLoc(FVector _newLoc);
	void			SetViewMode(ViewMode _newMode);
	void			OnFireSwitch(bool _firBtn); //탄알 발사(RayCast)

	class AGunWeapon* GetCurrentWeapon();
	class USkeletalMeshComponent* GetSkelMesh();

	//카메라 설정
	UPROPERTY(EditAnywhere, Category = Camera)
		UCameraComponent*		camera_;
	UPROPERTY(EditAnywhere, Category = Camera)
		USpringArmComponent*	cameraArm_;

	float		armLengthTo_;

	//Test
	//void	PlayTestMotion(bool _test);

	float			armRotationSpeed_;
	FRotator		armRotationTo_;
	FVector			directionToMove_;

private:
	UPROPERTY()
		class AGunWeapon*			weapon_;
	UPROPERTY()
		class AWarPlayerController*	playerController_;
	UPROPERTY()
		class UPlayerAnimInstance*	playerAnim_;

	bool		isFire_;
	bool		isSprint_;
	float		lookPitch_;
	FVector		socketLocation_;
	FVector		PlayerLocation_;
	FRotator	PlayerRotator_;
};
