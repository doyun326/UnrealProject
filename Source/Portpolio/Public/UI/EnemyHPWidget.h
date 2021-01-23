// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSetting/Portpolio.h"

#include "Blueprint/UserWidget.h"
#include "EnemyHPWidget.generated.h"

/**
 * 
 */
UCLASS()
class PORTPOLIO_API UEnemyHPWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void	BindCharacterStat(class UADEnemyStatComponent* _newCharacterStat);

protected:
	virtual void NativeConstruct() override;

	void	UpdateHpWidget();

private:
	TWeakObjectPtr<class UADEnemyStatComponent> currentCharacterStat_;

	UPROPERTY()
		class UProgressBar*		hpProgressBar_;
};
