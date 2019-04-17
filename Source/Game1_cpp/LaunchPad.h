// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LaunchPad.generated.h"

UCLASS()
class GAME1_CPP_API ALaunchPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALaunchPad();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	UFUNCTION(Category = "Collision")
	void ZoneOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UPROPERTY(EditDefaultsOnly, Category = "Collision")
	class UBoxComponent *LaunchZone;

	UPROPERTY(EditDefaultsOnly, Category = "Visual")
	class UStaticMeshComponent *LaunchPad;

	UPROPERTY(EditAnywhere, Category = "FX")
	class UParticleSystem *Effect;

	UPROPERTY(EditDefaultsOnly, Category = "Gameplay")
	class UArrowComponent *Direction;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
	float LauncchStr = 100.0f;


};
