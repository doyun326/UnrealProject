// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/UI/TitleUIWidget.h"

#include "EngineUtils.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

void UTitleUIWidget::NativeConstruct() 
{
	Super::NativeConstruct();

	newGameBtn_ = Cast<UButton>(GetWidgetFromName(TEXT("btnNewGame")));
	
	if (newGameBtn_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : newGameBtn"));
		return;
	}

	exitBtn_ = Cast<UButton>(GetWidgetFromName(TEXT("btnExit")));

	if (exitBtn_ == nullptr)
	{
		ABLOG(Error, TEXT("nulltpr : ExitBtn"));
		return;
	}

	newGameBtn_->OnClicked.AddDynamic(this, &UTitleUIWidget::OnNewGameClicked);
	exitBtn_->OnClicked.AddDynamic(this, &UTitleUIWidget::OnExitClicked);
}

void UTitleUIWidget::OnNewGameClicked()
{
	UGameplayStatics::OpenLevel(this, FName("SpaceShip_Loby"));

	ABLOG(Warning, TEXT("Click Exit Button Clicked!!!"));
}

void UTitleUIWidget::OnExitClicked()
{
	ABLOG(Warning, TEXT("Click Exit Button Clicked!!!"));
}