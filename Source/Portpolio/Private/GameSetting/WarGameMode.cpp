// Fill out your copyright notice in the Description page of Project Settings.


#include "GameSetting/WarGameMode.h"
#include "Character/Player/PlayerCharacter.h"
#include "Character/Player/WarPlayerController.h"
#include "UI/WarHUD.h"


AWarGameMode::AWarGameMode()
{
	//���⼭ ������ ���� ABPawn���͸� �����ϰ� �̸� �����ϴ� ���� �ƴ�, Ŭ���� ������ ����. (��Ƽ ���� ���)
	DefaultPawnClass = APlayerCharacter::StaticClass();
	PlayerControllerClass = AWarPlayerController::StaticClass();
	HUDClass = AWarHUD::StaticClass();
	//PlayerStateClass = AABPlayerState::StaticClass();
	//GameStateClass = AABGameState::StaticClass();
}

void AWarGameMode::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AWarGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}