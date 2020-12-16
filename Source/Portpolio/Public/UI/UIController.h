// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSetting/Portpolio.h"

#include "GameFramework/PlayerController.h"
#include "UIController.generated.h"

/**
 * 
 */
UCLASS()
class PORTPOLIO_API AUIController : public APlayerController
{
	GENERATED_BODY()

public:
	AUIController();

protected: 
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
		TSubclassOf<class UUserWidget> UIWidgetClass_;
	UPROPERTY()
		class UUserWidget*	UIWidgetInstance_;

};
