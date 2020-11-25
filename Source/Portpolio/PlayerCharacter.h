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
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
		void	OnFire();

	void	SetControllMode(ControlMode _newMode);
	void	SetViewMode(ViewMode _newMode);
	void	OnFireSwitch(bool _firBtn); //탄알 발사(RayCast)
	void	PlayMontageDiveJump();
	void	ChangeGripSocket();

	bool			GetIsShooting();
	ControlMode		GetCurrentControllMode();
	ViewMode		GetCurrentViewMode();

	//카메라 설정
	UPROPERTY(EditAnywhere, Category = Camera)
		UCameraComponent* camera_;
	UPROPERTY(EditAnywhere, Category = Camera)
		USpringArmComponent* cameraArm_;

	float			armLengthTo_;

	//TestView
	float			armRotationSpeed_;
	FRotator		armRotationTo_;
	FVector			directionToMove_;

private:
	bool	rayHit_;
	bool	isShooting_;
	FVector socketLocation_;

	FTimerHandle		shotDelayTimerHandle_;

	UPROPERTY()
		class AWarWeapon*			weapon_;
	UPROPERTY()
		class AWarPlayerController*	playerController_;
};
