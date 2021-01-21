// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSetting/Portpolio.h"

#include "GameFramework/PlayerState.h"
#include "WarPlayerState.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnPlayerStateChangeDelegate);

/**
 * 
 */
UCLASS()
class PORTPOLIO_API AWarPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	AWarPlayerState();

	int32	GetGameScore() const;
	int32	GetCharacterLevel() const;
	void	InitPlayerData();

	FOnPlayerStateChangeDelegate onPlayerStateChange;

protected:
	UPROPERTY(Transient)
		int32	gameScore_;
	UPROPERTY(Transient)
		int32	characterLevel_;

};
