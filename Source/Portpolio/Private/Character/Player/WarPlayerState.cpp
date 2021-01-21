// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Character/Player/WarPlayerState.h"

AWarPlayerState::AWarPlayerState()
{
	gameScore_ = 0;
	characterLevel_ = 1;
}

void AWarPlayerState::InitPlayerData()
{
	SetPlayerName(TEXT("Sica"));
	characterLevel_ = 5;
	gameScore_ = 0;
}

int32 AWarPlayerState::GetGameScore() const
{
	return gameScore_;
}

int32 AWarPlayerState::GetCharacterLevel() const
{
	return characterLevel_;
}
