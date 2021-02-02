// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSetting/Portpolio.h"

#include "Blueprint/UserWidget.h"
#include "MinionHPWidget.generated.h"

/**
 * 
 */
UCLASS()
class PORTPOLIO_API UMinionHPWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void	BindCharacterStat(class UMinionEnemyStatComponent* _newCharacterStat);

protected:
	virtual void NativeConstruct() override;

	void	UpdateHpWidget();

private:
	TWeakObjectPtr<class UMinionEnemyStatComponent> currentCharacterStat_;

	UPROPERTY()
		class UProgressBar* hpProgressBar_;
};
