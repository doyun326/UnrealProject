// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/UI/BossHPWidget.h"
#include "../Public/Character/Enemy/Boss/BossStatComponent.h"

#include "Components/ProgressBar.h"

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

	hpProgressBar_ = Cast<UProgressBar>(GetWidgetFromName(TEXT("HpBar")));

	if (hpProgressBar_ != nullptr)
	{
		ABLOG(Warning, TEXT("Success : hpProgressBar"));
		UpdateHpWidget();
	}
}

void UBossHPWidget::UpdateHpWidget()
{
	if (currentCharacterStat_.IsValid())
	{
		if (hpProgressBar_ != nullptr)
		{
			hpProgressBar_->SetPercent(currentCharacterStat_->GetHpRatio());
		}
	}
}