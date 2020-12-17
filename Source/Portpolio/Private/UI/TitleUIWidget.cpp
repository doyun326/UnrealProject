// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/UI/TitleUIWidget.h"

#include "EngineUtils.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"

void UTitleUIWidget::NativeConstruct()
{
	Super::NativeConstruct();

	newGameBtn_ = Cast<UButton>(GetWidgetFromName(TEXT("btnNewGame")));
	
	if (newGameBtn_ == nullptr)
	{
		ABLOG(Error, TEXT("new Game Btn Empty!"));
	}

	newGameBtn_->OnClicked.AddDynamic(this, &UTitleUIWidget::OnNewGameClicked);
}

void UTitleUIWidget::OnNewGameClicked()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Level02"));
}

void UTitleUIWidget::OnContinueClicked()
{

}

void UTitleUIWidget::OnExitClicked()
{

}