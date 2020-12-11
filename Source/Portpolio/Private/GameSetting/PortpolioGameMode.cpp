// Copyright Epic Games, Inc. All Rights Reserved.

#include "../Public/GameSetting/PortpolioGameMode.h"
#include "../Public/Character/PortpolioCharacter.h"
#include "UObject/ConstructorHelpers.h"

APortpolioGameMode::APortpolioGameMode()
{
	// set default pawn class to our Blueprinted character
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/StartPack/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
