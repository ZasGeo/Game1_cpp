// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Game1_cppGameMode.generated.h"

UCLASS(minimalapi)
class AGame1_cppGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, Category ="Gamplay")
	TSubclassOf<AActor> SpectatingClass;

public:
	AGame1_cppGameMode();



	void CompleteMission(APawn* InstigatorPawn, bool MissionSuccess);

	UFUNCTION(BlueprintImplementableEvent, Category = "Gameplay")
	void OnMissionComplete(APawn *InstigatorPawn, bool MissionSuccess);
};



