// Fill out your copyright notice in the Description page of Project Settings.


#include "LaunchPad.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Character.h"
#include "Components/ArrowComponent.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALaunchPad::ALaunchPad()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	

	LaunchZone = CreateDefaultSubobject<UBoxComponent>(TEXT("Zone"));
	RootComponent = LaunchZone;
	LaunchZone->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	LaunchZone->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	LaunchZone->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	LaunchZone->SetCollisionResponseToChannel(ECollisionChannel::ECC_PhysicsBody, ECollisionResponse::ECR_Overlap);
	

	LaunchPad = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Pad"));
	LaunchPad->SetupAttachment(RootComponent);

	Direction = CreateDefaultSubobject<UArrowComponent>(TEXT("Direction"));
	Direction->SetupAttachment(RootComponent);


	LaunchZone->OnComponentBeginOverlap.AddDynamic(this, &ALaunchPad::ZoneOverlap);

}

// Called when the game starts or when spawned
void ALaunchPad::BeginPlay()
{
	Super::BeginPlay();
	
}

void ALaunchPad::ZoneOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ACharacter *Char = Cast<ACharacter>(OtherActor);

	if (Char)
	{
		Char->LaunchCharacter(Direction->GetForwardVector()*LauncchStr, true, true);
		UGameplayStatics::SpawnEmitterAtLocation(this, Effect, GetActorLocation());
	}
	else if (OtherComp && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulse(Direction->GetForwardVector()*LauncchStr, NAME_None, true);
		UGameplayStatics::SpawnEmitterAtLocation(this, Effect, GetActorLocation());
	}

	
}

// Called every frame
void ALaunchPad::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

