// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSetting/Portpolio.h"

#include "Blueprint/UserWidget.h"
#include "BossHPWidget.generated.h"

/**
 * 
 */
UCLASS()
class PORTPOLIO_API UBossHPWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void	BindCharacterStat(class UBossStatComponent* _newCharacterStat);

protected:
	virtual void NativeConstruct() override;

	void	UpdateHpWidget();

private:
	TWeakObjectPtr<class UBossStatComponent> currentCharacterStat_;

	UPROPERTY()
		class UProgressBar* hpProgressBar_;
};
