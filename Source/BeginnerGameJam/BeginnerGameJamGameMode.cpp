// Copyright Epic Games, Inc. All Rights Reserved.

#include "BeginnerGameJamGameMode.h"
#include "BeginnerGameJamCharacter.h"
#include "UObject/ConstructorHelpers.h"

ABeginnerGameJamGameMode::ABeginnerGameJamGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
