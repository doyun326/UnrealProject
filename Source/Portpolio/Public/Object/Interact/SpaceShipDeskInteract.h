// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSetting/Portpolio.h"
#include "Object/BaseInteractable.h"

#include "SpaceShipDeskInteract.generated.h"

/**
 * 
 */
UCLASS()
class PORTPOLIO_API ASpaceShipDeskInteract : public ABaseInteractable
{
	GENERATED_BODY()
	
public:
	ASpaceShipDeskInteract();

	virtual void Interact() override;

	UPROPERTY()
		bool	state_;

protected:

private:
};
