// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSetting/Portpolio.h"

#include "Character/BaseCharacter.h"
#include "NpcOperator.generated.h"

/**
 * 
 */
UCLASS()
class PORTPOLIO_API ANpcOperator : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	ANpcOperator();

	virtual void	Tick(float DeltaTime) override;
	virtual void	SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void	PostInitializeComponents() override;
	virtual void	PossessedBy(AController* NewController) override;

protected:
	virtual void BeginPlay() override;

private:

};
