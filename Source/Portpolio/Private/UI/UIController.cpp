// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/UI/UIController.h"

#include "Blueprint/UserWidget.h"

AUIController::AUIController()
{

}

void AUIController::BeginPlay()
{
	Super::BeginPlay();

	UIWidgetInstance_ = CreateWidget<UUserWidget>(this, UIWidgetClass_);

	if (UIWidgetClass_ == nullptr || UIWidgetInstance_ == nullptr)
	{
		return;
	}

	UIWidgetInstance_->AddToViewport();

	FInputModeUIOnly Mode;
	Mode.SetWidgetToFocus(UIWidgetInstance_->GetCachedWidget());
	SetInputMode(Mode);
	bShowMouseCursor = true;
}