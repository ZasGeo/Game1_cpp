// Fill out your copyright notice in the Description page of Project Settings.


#include "AIGuard.h"
#include "Perception/PawnSensingComponent.h"
#include "DrawDebugHelpers.h"
#include "Game1_cppGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/TargetPoint.h"
#include "AIController.h"

// Sets default values
AAIGuard::AAIGuard() : GuardState { EAIState ::Idle} , CurrentPatrolPoint { 0 }
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PawnSensing = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("Sensing"));

	PawnSensing->OnSeePawn.AddDynamic(this, &AAIGuard::OnPawnSeen);
	PawnSensing->OnHearNoise.AddDynamic(this, &AAIGuard::OnNoiseHeard);

}

// Called when the game starts or when spawned
void AAIGuard::BeginPlay()
{
	Super::BeginPlay();

	OriginalRotation = GetActorRotation();

	if (bShouldPatrol)
	{
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ATargetPoint::StaticClass(), TargetPoints);
	}
	
	StartPatrol();
	
}

void AAIGuard::OnPawnSeen(APawn *SeenPawn)
{
	if (!SeenPawn)
	{
		return;
	}

	AGame1_cppGameMode *Gamemode = Cast<AGame1_cppGameMode>(GetWorld()->GetAuthGameMode());
	if (Gamemode)
	{
		Gamemode->CompleteMission(SeenPawn, false);
	}

	StopPatrol();

	SetGuardState(EAIState::Alerted);
}

void AAIGuard::OnNoiseHeard(APawn *NoiseInstigator, const FVector &Location, float volume)
{

	if (GuardState == EAIState::Alerted)
	{
		return;
	}

	StopPatrol();

	//DrawDebugSphere(GetWorld(), Location, 50.0f, 12, FColor::Green, false, 10.0f);

	FVector Direction = Location - GetActorLocation();

	Direction.Normalize();

	FRotator NewLookAt = FRotationMatrix::MakeFromX(Direction).Rotator();

	NewLookAt.Pitch = 0.0f;
	NewLookAt.Roll = 0.0f;

	SetActorRotation(NewLookAt);

	GetWorldTimerManager().ClearTimer(Timer_ResetOrientatiom);
	
	GetWorldTimerManager().SetTimer(Timer_ResetOrientatiom,this, &AAIGuard::ResetOrientation, 3.0f, false);

	
	SetGuardState(EAIState::Suspicious);

	
	

}

void AAIGuard::ResetOrientation()
{
	if (GuardState == EAIState::Alerted)
	{
		return;
	}

	StartPatrol();

	SetActorRotation(OriginalRotation);

	SetGuardState(EAIState::Idle);

}

void AAIGuard::SetGuardState(EAIState NewState)
{
	if (GuardState == NewState)
	{
		return;
	}

	GuardState = NewState;

	OnStateChanged(GuardState);
}

void AAIGuard::StartPatrol()
{
	if (TargetPoints.Num() == 0)
	{
		return;
	}

	GetWorldTimerManager().SetTimer(Timer_Patrol, this,  &AAIGuard::Patrol, 0.1f, true);
}

void AAIGuard::Patrol()
{
	
	//NPC->SpawnDefaultController();

	
	AAIController * moveController = Cast<AAIController>(GetController());

	// moves character to location defined by TargetLocation component of moveEvent	
	switch (moveController->MoveToActor(TargetPoints[CurrentPatrolPoint], 10.0f, true, true, false))
	{
	case EPathFollowingRequestResult::AlreadyAtGoal:
	{
		NextPoint();
		break;
	}
	case EPathFollowingRequestResult::RequestSuccessful:
	{
		break;
	}
	case EPathFollowingRequestResult::Failed:
	{
		NextPoint();
		break;
	}
	default:
		break;
	}
}

void AAIGuard::StopPatrol()
{
	GetWorldTimerManager().ClearTimer(Timer_Patrol);
	AAIController * moveController = Cast<AAIController>(GetController());
	moveController->StopMovement();
}

void AAIGuard::NextPoint()
{
	++CurrentPatrolPoint;

	if (CurrentPatrolPoint == TargetPoints.Num())
	{
		CurrentPatrolPoint = 0;
	}
	
}

// Called every frame
void AAIGuard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



