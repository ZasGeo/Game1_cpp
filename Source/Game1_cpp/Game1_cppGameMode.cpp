// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "Game1_cppGameMode.h"
#include "Game1_cppHUD.h"
#include "Game1_cppCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGame1_cppGameMode::AGame1_cppGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AGame1_cppHUD::StaticClass();
}
