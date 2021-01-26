// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSetting/WarGameMode.h"
#include "Character/Player/PlayerCharacter.h"
#include "Character/Player/WarPlayerController.h"
#include "../Public/Character/Player/WarPlayerState.h"

#include "UI/WarHUD.h"


AWarGameMode::AWarGameMode()
{
	//여기서 주의할 점은 ABPawn액터를 생성하고 이를 지정하는 것이 아닌, 클래스 정보를 지정. (멀티 게임 대비)
	DefaultPawnClass = APlayerCharacter::StaticClass();
	PlayerControllerClass = AWarPlayerController::StaticClass();
	PlayerStateClass = AWarPlayerState::StaticClass();
	HUDClass = AWarHUD::StaticClass();

	if (DefaultPawnClass == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : DefaultPawnClass"));
		return;
	}

	if (PlayerControllerClass == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : PlayerControllerClass"));
		return;
	}

	if (PlayerStateClass == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : PlayerStateClass"));
		return;
	}

	if (PlayerControllerClass == nullptr)
	{
		ABLOG(Error, TEXT("Error : PlayerControllerClass"));
		return;
	}

	if (HUDClass == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : HUDClass"));
		return;
	}
}

void AWarGameMode::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	DefaultPawnClass = APlayerCharacter::StaticClass();
	PlayerControllerClass = AWarPlayerController::StaticClass();
	HUDClass = AWarHUD::StaticClass();
}


void AWarGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	auto WarPlayerState = Cast<AWarPlayerState>(NewPlayer->PlayerState);

	if (WarPlayerState == nullptr)
	{
		ABLOG(Error, TEXT("Nullptr : PlayerState"));
		return;
	}

	WarPlayerState->InitPlayerData();
}