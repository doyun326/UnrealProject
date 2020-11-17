// Fill out your copyright notice in the Description page of Project Settings.


#include "WarPlayerController.h"
#include "PlayerCharacter.h"

AWarPlayerController::AWarPlayerController()
{
	pressFreeBtn_ = false;
}

void AWarPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AWarPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
}

void AWarPlayerController::ProcessPlayerInput(const float DeltaTime, const bool bGamePaused)
{
	bool pressFreeBtn_Old = pressFreeBtn_;
	APlayerCharacter* MyCharacter;
	MyCharacter = Cast<APlayerCharacter>(GetCharacter());

	Super::ProcessPlayerInput(DeltaTime, bGamePaused);

	if (MyCharacter != nullptr)
	{
		if (pressFreeBtn_Old && (pressFreeBtn_Old == pressFreeBtn_))
		{
			//MyCharacter->SetViewMode(ViewMode::FREEVIEW);
		}
		else
		{
			//MyCharacter->SetViewMode(ViewMode::COMMONVIEW);
		}
	}
}

void AWarPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAction(TEXT("FreeView"), EInputEvent::IE_Pressed, this, &AWarPlayerController::FreeViewModeStarted);
	InputComponent->BindAction(TEXT("FreeView"), EInputEvent::IE_Released, this, &AWarPlayerController::FreeViewModeReleased);
}

void AWarPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AWarPlayerController::FreeViewModeStarted()
{
	pressFreeBtn_ = true;
}

void AWarPlayerController::FreeViewModeReleased()
{
	pressFreeBtn_ = false;
}

