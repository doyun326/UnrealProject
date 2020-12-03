// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Portpolio.h"
#include "PlayerCharacter.h"
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

public:
	virtual void PostInitializeComponents() override;
	virtual void OnPossess(APawn* aPawn) override;
	virtual void ProcessPlayerInput(const float DeltaTime, const bool bGamePaused) override;

	bool	GetFireBtn();

protected:
	virtual void SetupInputComponent() override;
	virtual void BeginPlay() override;

private:
	void	ZoomInStarted();
	void	ZoomInReleased();
	void	DiveJump();
	void	RunSprintStart();
	void	RunSprintReleased();
	void	OnFireStart();
	void	OnFireReleased();

	bool		zoomInBtn_;
	bool		sprintBtn_;
	bool		fireBtn_;

	//Test
	void	OnTestMotionStart();
	void	OnTestMotionReleased();

	bool	testBtn_;

	APlayerCharacter*	myCharacter_;
	ViewMode			currentView_;
};
