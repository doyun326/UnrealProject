// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSetting/Portpolio.h"
#include "Character/Player/PlayerCharacter.h"

#include "GameFramework/PlayerController.h"
#include "WarPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class PORTPOLIO_API AWarPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AWarPlayerController();

	virtual void PostInitializeComponents() override;
	virtual void OnPossess(APawn* aPawn) override;
	virtual void ProcessPlayerInput(const float DeltaTime, const bool bGamePaused) override;

	bool	GetFireBtn();
	void	HideHUD();
	void	ShowHUD();

	class UPlayerHudWidget* GetHudWidget() const;

protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
		TSubclassOf<class UPlayerHudWidget>	hudWidgetClass_;

private:
	UPROPERTY()
		class UPlayerHudWidget* hudWidget_;
	UPROPERTY()
		class APlayerCharacter* myPlayer_;
	UPROPERTY()
		class AWarPlayerState*	myPlayerState_;
	UPROPERTY()
		class UWarGameInstance*	warInstance_;

	void	ZoomInStarted();
	void	ZoomInReleased();
	void	DiveJump();
	void	RunSprintStart();
	void	RunSprintReleased();
	void	OnFireStart();
	void	OnFireReleased();
	void	OnAvoid();
	void	OnInfinityMode();
	void	UpdateExp();

	bool	zoomInBtn_;
	bool	sprintBtn_;
	bool	fireBtn_;

	ViewMode	currentView_;
};
