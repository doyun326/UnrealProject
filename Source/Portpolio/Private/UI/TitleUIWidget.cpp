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
		ABLOG(Error, TEXT("newGameBtn Error!"));
	}

	continueBtn_ = Cast<UButton>(GetWidgetFromName(TEXT("btnContinue")));

	if (continueBtn_ == nullptr)
	{
		ABLOG(Error, TEXT("ContinueBtn Error!"));
	}

	exitBtn_ = Cast<UButton>(GetWidgetFromName(TEXT("btnExit")));

	if (exitBtn_ == nullptr)
	{
		ABLOG(Error, TEXT("ExitBtn Error!"));
	}

	newGameBtn_->OnClicked.AddDynamic(this, &UTitleUIWidget::OnNewGameClicked);
	continueBtn_->OnClicked.AddDynamic(this, &UTitleUIWidget::OnContinueClicked);
	exitBtn_->OnClicked.AddDynamic(this, &UTitleUIWidget::OnExitClicked);
}

void UTitleUIWidget::OnNewGameClicked()
{
	//UGameplayStatics::OpenLevel(GetWorld(), FName("Level02"), true, FString("?Game=/Game/My/Blueprints/GameSetting/WarGameMode_BP.WarGameMode_BP_C"));
	//UGameplayStatics::OpenLevel(GetWorld(), TEXT("Level02"), true, FString("Game = WAR"));
	UGameplayStatics::OpenLevel(this, FName("Level02"));

	ABLOG(Warning, TEXT("ASDASD"));
}

void UTitleUIWidget::OnContinueClicked()
{
	ABLOG(Warning, TEXT("Click Continue Button Clicked!!!"));
}

void UTitleUIWidget::OnExitClicked()
{
	ABLOG(Warning, TEXT("Click Exit Button Clicked!!!"));
}