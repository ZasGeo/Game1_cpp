// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "Game1_cppGameMode.h"
#include "Game1_cppHUD.h"
#include "Game1_cppCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "FPSGameState.h"

AGame1_cppGameMode::AGame1_cppGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AGame1_cppHUD::StaticClass();

	GameStateClass = AFPSGameState::StaticClass();
}

void AGame1_cppGameMode::CompleteMission(APawn* InstigatorPawn, bool MissionSuccess)
{
	if (InstigatorPawn)
	{
		TArray<AActor*> ReturnedActors;
		UGameplayStatics::GetAllActorsOfClass(this, SpectatingClass, ReturnedActors);

		if (ReturnedActors.Num() > 0)
		{
			for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; It++)
			{
				APlayerController *PC = It->Get();
				if (PC)
				{
					PC->SetViewTargetWithBlend(ReturnedActors[0], 1.0f, EViewTargetBlendFunction::VTBlend_Cubic);
				}
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Cannot change spectating viewtarget"));
		}

	

		AFPSGameState *GS = GetGameState<AFPSGameState>();

		if (GS)
		{
			GS->MulticastOnMissionComplete(InstigatorPawn, MissionSuccess);
		}

		OnMissionComplete(InstigatorPawn, MissionSuccess);

	}

	
}
