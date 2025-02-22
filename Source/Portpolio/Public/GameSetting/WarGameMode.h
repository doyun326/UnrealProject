// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSetting/Portpolio.h"
#include "GameFramework/GameModeBase.h"
#include "WarGameMode.generated.h"

/**
 * 
 */
UCLASS()
class PORTPOLIO_API AWarGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AWarGameMode();

protected:

public:

	virtual void PostInitializeComponents() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;

private:
	
};
