// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Character/Player/WarPlayerState.h"
#include "../Public/GameSetting/WarGameInstance.h"

AWarPlayerState::AWarPlayerState()
{
	gameScore_ = 0;
	characterLevel_ = 1;
	exp_ = 0;
}

void AWarPlayerState::InitPlayerData()
{
	SetPlayerName(TEXT("Sica"));
	characterLevel_ = 5;
	gameScore_ = 0;
	exp_ = 0;
}

int32 AWarPlayerState::GetGameScore() const
{
	return gameScore_;
}

int32 AWarPlayerState::GetCharacterLevel() const
{
	return characterLevel_;
}

float AWarPlayerState::GetExpRatio()
{
	if (currentStatData_->NextExp <= KINDA_SMALL_NUMBER)
	{
		return 0.0f;
	}
	//float Result = (float)exp_ / (float)currentStatData_->NextExp;


	return 0.0f;
}

bool AWarPlayerState::AddExp(int32 _inComeExp)
{
	if (currentStatData_->NextExp == -1)
	{
		return false;
	}

	bool DidLevelUp = false;
	exp_ = exp_ + _inComeExp;

	if (exp_ >= currentStatData_->NextExp)
	{
		exp_ -= currentStatData_->NextExp;
		SetCharacterLevel(characterLevel_ + 1);
		DidLevelUp = true;
	}

	onPlayerStateChange.Broadcast();

	return DidLevelUp;
}

void AWarPlayerState::SetCharacterLevel(int32 _newCharacterLevel)
{
	auto WarGameInstance = Cast<UWarGameInstance>(GetGameInstance());

	if (WarGameInstance == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : WarGameInstance"));
		return;
	}

	currentStatData_ = WarGameInstance->GetPlayerData(_newCharacterLevel);

	if (currentStatData_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : currentStatData"));
		return;
	}

	characterLevel_ = _newCharacterLevel;
}