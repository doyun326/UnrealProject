// Fill out your copyright notice in the Description page of Project Settings.


#include "WarGameMode.h"
#include "WarCharacter.h"

AWarGameMode::AWarGameMode()
{
	//���⼭ ������ ���� ABPawn���͸� �����ϰ� �̸� �����ϴ� ���� �ƴ�, Ŭ���� ������ ����. (��Ƽ ���� ���)
	DefaultPawnClass = AWarCharacter::StaticClass();
	//PlayerControllerClass = AABPlayerController::StaticClass();
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