// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Portpolio.h"
#include "BaseCharacter.h"
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

	void	SetViewMode(ViewMode _newMode);
	void	OnFireSwitch(bool _firBtn); //ź�� �߻�(RayCast)
	void	PlayMontageDiveJump();

	class AGunWeapon* GetCurrentWeapon();
	void SetWeaponLoc(FVector _newLoc);

	bool			GetIsFire();

	bool			GetSprintBtn();
	void			SetSprintBtn(bool _newState);

	ControlMode		GetCurrentControllMode();
	ViewMode		GetCurrentViewMode();
	FVector			GetPlayerLocation();
	FRotator		GetPlayerRotator();

	//ī�޶� ����
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
	FVector		socketLocation_;
	FVector		PlayerLocation_;
	FRotator	PlayerRotator_;


	FVector test;
};
