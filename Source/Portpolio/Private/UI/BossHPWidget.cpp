// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/UI/BossHPWidget.h"
#include "../Public/Character/Enemy/Boss/BossStatComponent.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UBossHPWidget::BindCharacterStat(class UBossStatComponent* _newCharacterStat)
{
	if (_newCharacterStat == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : newCharacterStat"));
		return;
	}

	currentCharacterStat_ = _newCharacterStat;
	_newCharacterStat->onHpChanged_.AddUObject(this, &UBossHPWidget::UpdateHpWidget);
}

void UBossHPWidget::NativeConstruct()
{
	Super::NativeConstruct();

	hpBar_ = Cast<UProgressBar>(GetWidgetFromName(TEXT("HpBar")));
	if(hpBar_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : hpBar"));
		return;
	}

	levelText_ = Cast<UTextBlock>(GetWidgetFromName(TEXT("LevelTextNum")));
	if (hpBar_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : levelText_"));
		return;
	}
}

void UBossHPWidget::UpdateHpWidget()
{
	if (currentCharacterStat_.IsValid())
	{
		if (hpBar_ != nullptr)
		{
			hpBar_->SetPercent(currentCharacterStat_->GetHpRatio());
		}
		if (levelText_ != nullptr)
		{
			levelText_->SetText(FText::FromString(FString::FromInt(currentCharacterStat_->GetLevel())));
		}
	}
}