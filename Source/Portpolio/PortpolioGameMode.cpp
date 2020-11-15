// Copyright Epic Games, Inc. All Rights Reserved.

#include "PortpolioGameMode.h"
#include "PortpolioCharacter.h"
#include "UObject/ConstructorHelpers.h"

APortpolioGameMode::APortpolioGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
