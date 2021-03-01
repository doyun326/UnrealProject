// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameSetting/Portpolio.h"

#include "GameFramework/Actor.h"
#include "DialogueMaker.generated.h"

UCLASS()
class PORTPOLIO_API ADialogueMaker : public AActor
{
	GENERATED_BODY()
	
public:	
	ADialogueMaker();

	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "UI")
		class UWidgetComponent* dialogueWidgetClass_;

	void Test();

	int32 asxd;
	
protected:
	virtual void BeginPlay() override;

public:	
	UPROPERTY()
		class UAIDeskInteractionWidget* dialougeWidget_;

};
