// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ExtractionZone.generated.h"

UCLASS()
class GAME1_CPP_API AExtractionZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AExtractionZone();

protected:
	

	UPROPERTY(VisibleAnywhere, Category = "Collision")
	class UBoxComponent *OverlapComp;

	UPROPERTY(VisibleAnywhere, Category = "Visual")
	class UDecalComponent *Decal;

	UPROPERTY(EditDefaultsOnly, Category = "SFX")
	class USoundBase *ObjectiveMissingSound;

	UFUNCTION(Category = "Collision")
	void CompOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	


};
