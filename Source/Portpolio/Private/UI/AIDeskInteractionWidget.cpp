// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/UI/AIDeskInteractionWidget.h"

#include "Components/Border.h"
#include "Components/TextBlock.h"

void UAIDeskInteractionWidget::NativeConstruct()
{
	Super::NativeConstruct();

	dialogueBorder_ = Cast<UBorder>(GetWidgetFromName(TEXT("DialogueWindow")));
	if (dialogueBorder_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : dialogueBorder_"));
		return;
	}

	dialogueText_ = Cast<UTextBlock>(GetWidgetFromName(TEXT("DialogueText")));
	if (dialogueText_ == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : dialogueText_"));
		return;
	}
}

void UAIDeskInteractionWidget::SetDialogueText(TArray<FString> _texts)
{
	if (dialogueTexts_.Num() == 0)
	{
		dialogueTexts_ = _texts;
	}
	UpdateDialogueText();
}

void UAIDeskInteractionWidget::UpdateDialogueText(int32 _rowNum)
{
	dialogueText_->SetText(FText::FromString(dialogueTexts_[_rowNum]));
}
