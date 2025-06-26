// Copyright Epic Games, Inc. All Rights Reserved.

#include "prototypeCyrusGameMode.h"
#include "prototypeCyrusCharacter.h"
#include "UObject/ConstructorHelpers.h"

AprototypeCyrusGameMode::AprototypeCyrusGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
