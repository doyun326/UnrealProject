// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/UI/EnemyHPWidget.h"
#include "../Public/Character/Enemy/ADEnemyStatComponent.h"

#include "Components/ProgressBar.h"

void UEnemyHPWidget::BindCharacterStat(class UADEnemyStatComponent* _newCharacterStat)
{
	if (_newCharacterStat == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : newCharacterStat"));
		return;
	}

	currentCharacterStat_ = _newCharacterStat;
	_newCharacterStat->onHpChanged_.AddUObject(this, &UEnemyHPWidget::UpdateHpWidget);
	/*_newCharacterStat->onHpChanged_.AddLambda([this]()->void
		{
			if (currentCharacterStat_.IsValid())
			{
				ABLOG(Warning, TEXT("HPRatio : %f"), currentCharacterStat_->GetHpRatio());
			}
		}
	);*/
}

void UEnemyHPWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	hpProgressBar_ = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HPBar")));

	if (hpProgressBar_ != nullptr)
	{
		ABLOG(Warning, TEXT("Success : hpProgressBar"));
		UpdateHpWidget();
	}
}

void UEnemyHPWidget::UpdateHpWidget()
{
	if (currentCharacterStat_.IsValid())
	{
		if (hpProgressBar_ != nullptr)
		{
			hpProgressBar_->SetPercent(currentCharacterStat_->GetHpRatio());
		}
	}
}