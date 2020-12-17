// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/UI/TitleGameMode.h"
#include "../Public/UI/UIController.h"

ATitleGameMode::ATitleGameMode()
{
	PlayerControllerClass = AUIController::StaticClass();
	DefaultPawnClass = APawn::StaticClass();

}