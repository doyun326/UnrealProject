// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/UI/PlayerHudWidget.h"
#include "../Public/Character/Player/PlayerStatComponent.h"
#include "../Public/Character/Player/WarPlayerState.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/Border.h"

void UPlayerHudWidget::BindPlayerStat(class UPlayerStatComponent* _playerStat)
{
	if (_playerStat == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : playerStat"));
		return;
	}
	currentPlayerStat_ = _playerStat;
	currentPlayerStat_->onHpChanged_.AddUObject(this, &UPlayerHudWidget::UpdatePlayerStat);
	currentPlayerStat_->onMpChanged_.AddUObject(this, &UPlayerHudWidget::UpdatePlayerStat);
}

void UPlayerHudWidget::BindWarPlayerState(class AWarPlayerState* _playerState)
{
	if (_playerState == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : playerState"));
		return;
	}
	currentWarPlayerState_ = _playerState;
	currentWarPlayerState_->onPlayerStateChange.AddUObject(this, &UPlayerHudWidget::UpdateWarPlayerState);
	currentWarPlayerState_->onInteractChange.AddUObject(this, &UPlayerHudWidget::isHideInteractText);
}

void UPlayerHudWidget::NativeConstruct()
{
	Super::NativeConstruct();

	hpBar_ = Cast<UProgressBar>(GetWidgetFromName(TEXT("HpBar")));
	if (hpBar_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : hpBar_"));
		return;
	}

	mpBar_ = Cast<UProgressBar>(GetWidgetFromName(TEXT("MpBar")));
	if (mpBar_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : mpBar_"));
		return;
	}

	expBar_ = Cast<UProgressBar>(GetWidgetFromName(TEXT("ExpBar")));
	if (expBar_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : expBar_"));
		return;
	}

	levelText_ = Cast<UTextBlock>(GetWidgetFromName(TEXT("LevelTextNum")));
	if (hpBar_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : levelText_"));
		return;
	}

	hpText_ = Cast<UTextBlock>(GetWidgetFromName(TEXT("HPTextNum")));
	if (hpBar_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : hpText_"));
		return;
	}

	mpText_ = Cast<UTextBlock>(GetWidgetFromName(TEXT("MPTextNum")));
	if (hpBar_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : mpText_"));
		return;
	}

	expText_ = Cast<UTextBlock>(GetWidgetFromName(TEXT("EXPTextNum")));
	if (hpBar_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : expText_"));
		return;
	}

	interactText_ = Cast<UTextBlock>(GetWidgetFromName(TEXT("InteractBar")));
	if (interactText_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : interactText_"));
		return;
	}
}

void UPlayerHudWidget::UpdatePlayerStat()
{
	if (currentPlayerStat_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : currentPlayerStat_"));
		return;
	}
	levelText_->SetText(FText::FromString(FString::FromInt(currentWarPlayerState_->GetCharacterLevel())));
	hpText_->SetText(FText::FromString(FString::FromInt(currentPlayerStat_->GetHpText())));
	hpBar_->SetPercent(currentPlayerStat_->GetHpRatio());
	mpText_->SetText(FText::FromString(FString::FromInt(currentPlayerStat_->GetMpText())));
	mpBar_->SetPercent(currentPlayerStat_->GetMpRatio());
}

void UPlayerHudWidget::UpdateWarPlayerState()
{
	if (currentWarPlayerState_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : currentWarPlayerState"));
		return;
	}
	expBar_->SetPercent(currentWarPlayerState_->GetExpRatio());
	expText_->SetText(FText::FromString(FString::FromInt(currentWarPlayerState_->GetExp())));
}

void UPlayerHudWidget::isHideInteractText(bool _view)
{
	if (_view)
	{
		interactText_->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		interactText_->SetVisibility(ESlateVisibility::Hidden);
	}
}