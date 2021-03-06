// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Character/Player/WarPlayerState.h"
#include "../Public/GameSetting/WarGameInstance.h"

AWarPlayerState::AWarPlayerState()
{
	gameScore_ = 0;
	exp_ = 0;
}

void AWarPlayerState::InitPlayerData()
{
	warGameInstance_ = Cast<UWarGameInstance>(GetGameInstance());

	if (warGameInstance_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : warGameInstance_"));
		return;
	}

	ABLOG_S(Error);
	SetPlayerName(TEXT("Sica"));
	characterLevel_ = warGameInstance_->GetPlayerLevel();
	SetCharacterLevel(characterLevel_);
	gameScore_ = 0;
	exp_ = 0;
}

float AWarPlayerState::GetExpRatio() const
{
	if (currentStatData_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : currentStatData"));
		return 0.0f;
	}
	if (currentStatData_->NextExp <= KINDA_SMALL_NUMBER)
	{
		return 0.0f;
	}

	float Result = (float)exp_ / (float)currentStatData_->NextExp;

	return Result;
}

bool AWarPlayerState::AddExp(int32 _inComeExp)
{
	if (currentStatData_ == nullptr)
	{
		ABLOG(Error, TEXT("Nulltpr : currentStatData"));
		return false;
	}
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

	ABLOG(Error, TEXT("%d"), exp_);

	onPlayerStateChange.Broadcast();

	return DidLevelUp;
}

void AWarPlayerState::SetCharacterLevel(int32 _newCharacterLevel)
{
	if (warGameInstance_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : warGameInstance_"));
		return;
	}

	currentStatData_ = warGameInstance_->GetPlayerData(_newCharacterLevel);

	if (currentStatData_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : currentStatData"));
		return;
	}

	characterLevel_ = _newCharacterLevel;
}

int32 AWarPlayerState::GetGameScore() const
{
	return gameScore_;
}

int32 AWarPlayerState::GetCharacterLevel() const
{
	return characterLevel_;
}

int32 AWarPlayerState::GetLimitLevel()
{
	if (UGameplayStatics::GetCurrentLevelName(GetWorld()) == "Stage_02")
	{
		characterLevel_ += 5;
	}
	else
	{
		characterLevel_ += 10;
	}
	warGameInstance_->SetPlayerLevel(characterLevel_);
	return characterLevel_;
}

int32 AWarPlayerState::GetExp()
{
	return exp_;
}

void AWarPlayerState::ChangeInteractText(bool _isView)
{
	warGameInstance_ = Cast<UWarGameInstance>(GetGameInstance());

	if (warGameInstance_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : WarGameInstance"));
		return;
	}

	if (!warGameInstance_->GetCheckAddViewport())
	{
		if (_isView)
		{
			onInteractChange.Broadcast(true);
		}
		else
		{
			onInteractChange.Broadcast(false);
		}
	}
	else
	{
		onInteractChange.Broadcast(false);
	}
}