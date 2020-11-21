// Fill out your copyright notice in the Description page of Project Settings.


#include "WarHUD.h"
#include "Engine/Canvas.h"
#include "Engine/Texture2D.h"
#include "TextureResource.h"
#include "CanvasItem.h"
#include "UObject/ConstructorHelpers.h"

AWarHUD::AWarHUD()
{
	static ConstructorHelpers::FObjectFinder<UTexture2D> CROSSHAIR_OBJ(TEXT("/Game/My/Asset/CrossHairs/Textures/Crosshairs/Crosshair_Arrow_8.Crosshair_Arrow_8"));

	if (CROSSHAIR_OBJ.Succeeded())
	{
		crossHair_ = CROSSHAIR_OBJ.Object;
	}
	else
	{
		ABLOG(Warning, TEXT("HUD Finder Faild!"))
	}
}

void AWarHUD::DrawHUD()
{
	Super::DrawHUD();

	const FVector2D Center(Canvas->ClipX * 0.5f, Canvas->ClipY * 0.5f);
	const FVector2D CrosshairDrawPosition(	(Center.X - 40.0f), 
											(Center.Y - 35.0f));

	FCanvasTileItem TileItem(CrosshairDrawPosition, crossHair_->Resource, FLinearColor::White);
	TileItem.BlendMode = SE_BLEND_Translucent;
	Canvas->DrawItem(TileItem);
}