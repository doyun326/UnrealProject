// Fill out your copyright notice in the Description page of Project Settings.


//#include "BaseCharacter.h"
#include "../Public/Character/BaseCharacter.h"
//#include "PlayerCharacter.h"

#define JUMP_POWER		 400.0f		//점프 파워 설정

ABaseCharacter::ABaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//점프 파워 설정
	GetCharacterMovement()->JumpZVelocity = JUMP_POWER;
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!isRight_ && !isFoward_)
	{
		isWalk_ = false;
	}
	else
	{
		isWalk_ = true;
	}
}

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ABaseCharacter::Jump);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ABaseCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ABaseCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ABaseCharacter::Turn);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &ABaseCharacter::LookUp);
}

//이동(앞, 뒤)
void ABaseCharacter::MoveForward(float _newAxisValue)
{
	if (_newAxisValue == -1 || _newAxisValue == 1)
	{
		isFoward_ = true;
	}
	else
	{
		isFoward_ = false;
	}
	AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::X), _newAxisValue);
}

//이동(좌, 우)
void ABaseCharacter::MoveRight(float _newAxisValue)
{
	if (_newAxisValue == -1 || _newAxisValue == 1)
	{
		isRight_ = true;
	}
	else
	{
		isRight_ = false;
	}
	AddMovementInput(FRotationMatrix(GetControlRotation()).GetUnitAxis(EAxis::Y), _newAxisValue);
}

void ABaseCharacter::LookUp(float _newAxisValue)
{
	AddControllerPitchInput(_newAxisValue);
}

void ABaseCharacter::Turn(float _newAxisValue)
{
	AddControllerYawInput(_newAxisValue);
}