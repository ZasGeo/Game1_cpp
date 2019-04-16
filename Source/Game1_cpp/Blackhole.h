// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Blackhole.generated.h"

class USphereComponent;

UCLASS()
class GAME1_CPP_API ABlackhole : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlackhole();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(Category = "Collision")
	void HorizonOverpap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category = "Collision")
	USphereComponent *AttractionRadious;

	UPROPERTY(VisibleAnywhere, Category = "Visual")
	UStaticMeshComponent *Horizon;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
	float AttractionStrenght = 0.0f;

};
