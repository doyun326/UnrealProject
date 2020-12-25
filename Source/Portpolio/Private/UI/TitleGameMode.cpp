// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/UI/TitleGameMode.h"
#include "../Public/UI/UIController.h"

ATitleGameMode::ATitleGameMode()
{
	DefaultPawnClass = APawn::StaticClass();
	PlayerControllerClass = AUIController::StaticClass();
	//DefaultPawnClass = APlayerCharacter::StaticClass();
}