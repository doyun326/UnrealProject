// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSetting/Portpolio.h"

#include "Blueprint/UserWidget.h"
#include "AIDeskInteractionWidget.generated.h"

/**
 * 
 */
UCLASS()
class PORTPOLIO_API UAIDeskInteractionWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void	SetDialogueText(TArray<FString> _texts);
	void	UpdateDialogueText(int32 _rowNum = 0);
	void	DialogueEmpty();

protected:
	virtual void NativeConstruct()	override;

private:
	UPROPERTY()
		class UBorder*		dialogueBorder_;
	UPROPERTY()
		class UTextBlock*	dialogueText_;
	
	TArray<FString> dialogueTexts_;
};
