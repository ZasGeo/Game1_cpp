// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSGameState.h"
#include "FPSPlayerController.h"

void AFPSGameState::MulticastOnMissionComplete_Implementation(APawn *InstigatorPawn, bool bMissionSuccess)
{
	/*for (FConstPawnIterator It = GetWorld()->GetPawnIterator(); It; It++)
	{
		APawn *Pawn = It->Get();
		if (Pawn && Pawn->IsLocallyControlled())
		{
			Pawn->DisableInput(nullptr);
		}
	}*/

	for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; It++)
	{
		AFPSPlayerController *PCont = Cast<AFPSPlayerController>(It->Get());

		if (PCont && PCont->IsLocalController())
		{
			PCont->OnMissionCompleted(InstigatorPawn, bMissionSuccess);

			APawn *MyPawn = PCont->GetPawn();
			if (MyPawn)
			{
				MyPawn->DisableInput(PCont);
			}
		}
		
	}
}
