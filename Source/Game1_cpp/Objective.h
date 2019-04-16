// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Objective.generated.h"

class USphereComponent;

UCLASS()
class GAME1_CPP_API AObjective : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AObjective();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void PlayEffect();

	UPROPERTY(VisibleAnywhere, Category = "Components")
	UStaticMeshComponent *MeshComp;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	USphereComponent *SphereComp;

	UPROPERTY(EditDefaultsOnly, Category="FX")
	UParticleSystem *PickupFX;

public:	
	

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
