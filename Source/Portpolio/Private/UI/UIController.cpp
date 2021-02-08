// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/UI/UIController.h"

#include "Blueprint/UserWidget.h"

#define TITLEUI_PATH "/Game/My/Blueprints/UI/UI_Title.UI_Title_C"

AUIController::AUIController()
{
	//Title UI Object
	static ConstructorHelpers::FObjectFinder<UClass> TITLE_UI(TEXT(TITLEUI_PATH));

	if (TITLE_UI.Succeeded())
	{
		ABLOG(Warning, TEXT("Success : TITLE_UI"));
		UIWidgetClass_ = (UClass*)TITLE_UI.Object;
	}
}

void AUIController::BeginPlay()
{
	Super::BeginPlay();

	UIWidgetInstance_ = CreateWidget<UUserWidget>(this, UIWidgetClass_);

	if (UIWidgetClass_ == nullptr || UIWidgetInstance_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : UIWidgetInstance"));
		return;
	}

	UIWidgetInstance_->AddToViewport();

	FInputModeUIOnly Mode;
	Mode.SetWidgetToFocus(UIWidgetInstance_->GetCachedWidget());
	SetInputMode(Mode);
	bShowMouseCursor = true;
}