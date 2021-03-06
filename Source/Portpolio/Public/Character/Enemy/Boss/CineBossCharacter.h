// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSetting/Portpolio.h"

#include "Character/BaseCharacter.h"
#include "CineBossCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PORTPOLIO_API ACineBossCharacter : public ABaseCharacter
{
	GENERATED_BODY()
	
public:
	ACineBossCharacter();

protected:
	virtual void BeginPlay() override;

private:

};
