// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSetting/Portpolio.h"

#include "GameFramework/PlayerState.h"
#include "WarPlayerState.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnPlayerStateChangeDelegate);
DECLARE_MULTICAST_DELEGATE_OneParam(FOnInteractionTextDelegate, bool);

/**
 * 
 */
UCLASS()
class PORTPOLIO_API AWarPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	AWarPlayerState();

	void	InitPlayerData();
	int32	GetGameScore() const;
	int32	GetCharacterLevel() const;
	float	GetExpRatio();
	bool	AddExp(int32 _inComeExp);
	void	ChangeInteractText(bool _isView);

	FOnPlayerStateChangeDelegate	onPlayerStateChange;
	FOnInteractionTextDelegate		onInteractChange;

protected:
	UPROPERTY(Transient)
		int32	gameScore_;
	UPROPERTY(Transient)
		int32	characterLevel_;
	UPROPERTY(Transient)
		int32	exp_;

private:
	void	SetCharacterLevel(int32 newCharacterLevel);
	struct	FPlayerData* currentStatData_;
};
