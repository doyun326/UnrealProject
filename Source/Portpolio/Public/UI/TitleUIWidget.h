// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSetting/Portpolio.h"
#include "Blueprint/UserWidget.h"
#include "TitleUIWidget.generated.h"

/**
 * 
 */
UCLASS()
class PORTPOLIO_API UTitleUIWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

	UPROPERTY()
		class UButton* newGameBtn_;
	UPROPERTY()
		class UButton* continueBtn_;
	UPROPERTY()
		class UButton* exitBtn_;

private:
	UFUNCTION()
		void OnNewGameClicked();
	UFUNCTION()
		void OnContinueClicked();
	UFUNCTION()
		void OnExitClicked();
};
