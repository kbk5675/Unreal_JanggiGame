#include "MovingActor.h"
#include "Components/StaticMeshComponent.h"

AMovingActor::AMovingActor()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
}

void AMovingActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AMovingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector NewLocation = GetActorLocation();

	/*Timer += DeltaTime;

	
	NewLocation.Y += FMath::Cos(Timer);
	SetActorLocation(NewLocation);*/

	float DeltaHeight = (FMath::Sin(Timer + DeltaTime) - FMath::Sin(Timer));
	NewLocation.Z += DeltaHeight * 100.0f;       //Scale our height by a factor of 20
	Timer += DeltaTime;
	SetActorLocation(NewLocation);
}

