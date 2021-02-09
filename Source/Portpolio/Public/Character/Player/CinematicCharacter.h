// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSetting/Portpolio.h"

#include "Character/BaseCharacter.h"
#include "CinematicCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PORTPOLIO_API ACinematicCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	ACinematicCharacter();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void PostInitializeComponents() override;

protected:
	virtual void BeginPlay() override;

private:
	
};
