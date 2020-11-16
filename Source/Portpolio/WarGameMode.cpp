// Fill out your copyright notice in the Description page of Project Settings.


#include "WarGameMode.h"
#include "WarCharacter.h"

AWarGameMode::AWarGameMode()
{
	//여기서 주의할 점은 ABPawn액터를 생성하고 이를 지정하는 것이 아닌, 클래스 정보를 지정. (멀티 게임 대비)
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