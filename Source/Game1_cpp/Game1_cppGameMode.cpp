// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "Game1_cppGameMode.h"
#include "Game1_cppHUD.h"
#include "Game1_cppCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"

AGame1_cppGameMode::AGame1_cppGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = AGame1_cppHUD::StaticClass();
}

void AGame1_cppGameMode::CompleteMission(APawn* InstigatorPawn, bool MissionSuccess)
{
	if (InstigatorPawn)
	{
		InstigatorPawn->DisableInput(nullptr);

		APlayerController *PController = Cast<APlayerController>(InstigatorPawn->GetController());

		if (PController)
		{
			TArray<AActor*> ReturnedActors;
			UGameplayStatics::GetAllActorsOfClass(this, SpectatingClass, ReturnedActors);
			
			if (ReturnedActors.Num() > 0)
			{
				PController->SetViewTargetWithBlend(ReturnedActors[0], 1.0f, EViewTargetBlendFunction::VTBlend_Cubic);
			}
			else
			{
				UE_LOG(LogTemp, Warning, TEXT("Cannot change spectating viewtarget"));
			}
							
		}

	}

	OnMissionComplete(InstigatorPawn, MissionSuccess);

	



}
