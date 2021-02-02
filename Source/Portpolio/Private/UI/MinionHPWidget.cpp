// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/UI/MinionHPWidget.h"
#include "../Public/Character/Enemy/Minion/MinionEnemyStatComponent.h"

#include "Components/ProgressBar.h"

void UMinionHPWidget::BindCharacterStat(class UMinionEnemyStatComponent* _newCharacterStat)
{
	if (_newCharacterStat == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : newCharacterStat"));
		return;
	}

	currentCharacterStat_ = _newCharacterStat;
	_newCharacterStat->onHpChanged_.AddUObject(this, &UMinionHPWidget::UpdateHpWidget);
	/*_newCharacterStat->onHpChanged_.AddLambda([this]()->void
		{
			if (currentCharacterStat_.IsValid())
			{
				ABLOG(Warning, TEXT("HPRatio : %f"), currentCharacterStat_->GetHpRatio());
			}
		}
	);*/
}

void UMinionHPWidget::NativeConstruct()
{
	Super::NativeConstruct();

	hpProgressBar_ = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HPBar")));

	if (hpProgressBar_ != nullptr)
	{
		ABLOG(Warning, TEXT("Success : hpProgressBar"));
		UpdateHpWidget();
	}
}

void UMinionHPWidget::UpdateHpWidget()
{
	if (currentCharacterStat_.IsValid())
	{
		if (hpProgressBar_ != nullptr)
		{
			hpProgressBar_->SetPercent(currentCharacterStat_->GetHpRatio());
		}
	}
}