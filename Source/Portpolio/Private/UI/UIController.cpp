// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/UI/UIController.h"

#include "Blueprint/UserWidget.h"

AUIController::AUIController()
{
	//Title UI Object
	static ConstructorHelpers::FObjectFinder<UClass> TITLE_UI(TEXT("/Game/My/Asset/UI/UI_Title.UI_Title_C"));

	if (TITLE_UI.Succeeded())
	{
		UIWidgetClass_ = (UClass*)TITLE_UI.Object;
	}
}

void AUIController::BeginPlay()
{
	Super::BeginPlay();

	UIWidgetInstance_ = CreateWidget<UUserWidget>(this, UIWidgetClass_);

	if (UIWidgetClass_ == nullptr || UIWidgetInstance_ == nullptr)
	{
		ABLOG(Warning, TEXT("UI Widget Error!"));
		return;
	}

	UIWidgetInstance_->AddToViewport();

	FInputModeUIOnly Mode;
	Mode.SetWidgetToFocus(UIWidgetInstance_->GetCachedWidget());
	SetInputMode(Mode);
	bShowMouseCursor = true;
}