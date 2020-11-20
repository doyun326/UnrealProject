// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Portpolio.h"
#include "GameFramework/HUD.h"
#include "WarHUD.generated.h"

/**
 * 
 */
UCLASS()
class PORTPOLIO_API AWarHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	AWarHUD();

	virtual void DrawHUD()	override;

private:
	class UTexture2D* crossHair_;
};
