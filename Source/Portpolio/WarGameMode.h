// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

public:

	virtual void PostInitializeComponents() override;
	virtual void PostLogin(APlayerController* NewPlayer) override;

private:
	
};
