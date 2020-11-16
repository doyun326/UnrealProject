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

	EControlMode	currentControlMode_;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void	SetControllMode(EControlMode _newMode);

	//카메라 설정
	UPROPERTY(EditAnywhere, Category = Camera)
		UCameraComponent* camera_;
	UPROPERTY(EditAnywhere, Category = Camera)
		USpringArmComponent* cameraArm_;

	float			armLengthTo_;
	EControlMode	GetCurrentControllMode();

};
