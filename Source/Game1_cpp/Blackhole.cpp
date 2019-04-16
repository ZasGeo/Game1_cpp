// Fill out your copyright notice in the Description page of Project Settings.


#include "Blackhole.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"


// Sets default values
ABlackhole::ABlackhole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AttractionRadious = CreateDefaultSubobject<USphereComponent>(TEXT("AttSphere"));
	AttractionRadious->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	AttractionRadious->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	AttractionRadious->SetCollisionResponseToChannel(ECollisionChannel::ECC_PhysicsBody, ECollisionResponse::ECR_Overlap);

	RootComponent = AttractionRadious;
	

	Horizon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("HorizonSphere"));
	Horizon->SetupAttachment(RootComponent);
	Horizon->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Horizon->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	Horizon->SetCollisionResponseToChannel(ECollisionChannel::ECC_PhysicsBody, ECollisionResponse::ECR_Overlap);

	Horizon->OnComponentBeginOverlap.AddDynamic(this, &ABlackhole::HorizonOverpap);

}

// Called when the game starts or when spawned
void ABlackhole::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABlackhole::HorizonOverpap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	OtherActor->Destroy();
}

// Called every frame
void ABlackhole::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);

	TArray<UPrimitiveComponent*> Components;
	AttractionRadious->GetOverlappingComponents(Components);
	for (UPrimitiveComponent* Component : Components)
	{
		if (Component && Component->IsSimulatingPhysics())
		{

			//FVector ForceDirection = GetActorLocation() - Component->GetComponentLocation();
			//Component->AddForce(ForceDirection*AttractionStrenght);
			Component->AddRadialForce(GetActorLocation(), AttractionRadious->GetScaledSphereRadius(), -AttractionStrenght, ERadialImpulseFalloff::RIF_Constant, true);
		}
	}
	
}

