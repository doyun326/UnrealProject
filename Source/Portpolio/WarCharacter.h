// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Portpolio.h"
#include "GameFramework/Character.h"
#include "WarCharacter.generated.h"

/*
* Player캐릭터 정의
*/

UCLASS()
class PORTPOLIO_API AWarCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AWarCharacter();

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

	EControlMode	GetCurrentControllMode();

	//카메라 설정
	UPROPERTY(EditAnywhere, Category = Camera)
		UCameraComponent*		camera_;
	UPROPERTY(EditAnywhere, Category = Camera)
		USpringArmComponent*	cameraArm_;

	float			armLengthTo_;

private:
	//Controll 관련
	void	MoveForward(float _newAxisValue);
	void	MoveRight(float _newAxisValue);
	void	LookUp(float _newAxisValue);
	void	Turn(float _newAxisValue);

};
