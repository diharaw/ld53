// Copyright Epic Games, Inc. All Rights Reserved.

#include "LD53GameMode.h"
#include "LD53Character.h"
#include "UObject/ConstructorHelpers.h"

ALD53GameMode::ALD53GameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
