// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSetting/Portpolio.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHudWidget.generated.h"

/**
 * 
 */
UCLASS()
class PORTPOLIO_API UPlayerHudWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void	BindPlayerStat(class UPlayerStatComponent* _playerStat);
	void	BindWarPlayerState(class AWarPlayerState* _playerState);

protected:
	virtual void NativeConstruct()	override;
	
	void	UpdatePlayerStat();
	void	UpdateWarPlayerState();

private:
	TWeakObjectPtr<class UPlayerStatComponent>	currentPlayerStat_;
	TWeakObjectPtr<class AWarPlayerState>		currentWarPlayerState_;

	UPROPERTY()
		class UProgressBar* hpBar_;
	UPROPERTY()
		class UProgressBar* mpBar_;
	UPROPERTY()
		class UProgressBar* expBar_;

	UPROPERTY()
		class UTextBlock*	levelText_;
	UPROPERTY()
		class UTextBlock*	hpText_;
	UPROPERTY()
		class UTextBlock*	mpText_;
	UPROPERTY()
		class UTextBlock*	expText_;
	
};
