// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AIGuard.generated.h"



UENUM(BlueprintType)
enum class EAIState : uint8 
{
	Idle,
	Suspicious,
	Alerted
};

UCLASS()
class GAME1_CPP_API AAIGuard : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAIGuard();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(Category = "Sensing")
	void OnPawnSeen(APawn *SeenPawn);

	UFUNCTION(Category = "Sensing")
	void OnNoiseHeard(APawn *NoiseInstigator, const FVector &Location, float volume);

	UFUNCTION()
	void ResetOrientation();

	void SetGuardState(EAIState NewState);

	UFUNCTION(BlueprintImplementableEvent, Category = "State")
	void OnStateChanged(EAIState NewState);

	void StartPatrol();

	UFUNCTION()
	void Patrol();

	void StopPatrol();

	void NextPoint();

	UFUNCTION()
	void OnRep_GuardState();

	//Change to ai perception
	UPROPERTY(VisibleAnywhere, Category = "Sensing")
	class UPawnSensingComponent *PawnSensing;

	FRotator OriginalRotation;

	FTimerHandle Timer_Patrol;

	FTimerHandle Timer_ResetOrientatiom;

	UPROPERTY(ReplicatedUsing=OnRep_GuardState)
	EAIState GuardState;


	TArray<AActor*> TargetPoints;

	uint32_t CurrentPatrolPoint;

	UPROPERTY(EditInstanceOnly, Category = "Patrol")
	bool bShouldPatrol;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	
};
