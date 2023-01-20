// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "TimerManager.h"

// Sets default values
AGun::AGun()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;

	BaseScene = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Scene"));
	RootComponent = BaseScene;

	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun Skeletal Mesh"));
	GunMesh->SetupAttachment(RootComponent);

	ProjectileSpawnPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(RootComponent);
}

void AGun::SetTargetLocation(FVector Location)
{
	TargetLocation = Location;
	GlobalTargetLocation.Set(TargetLocation.X, TargetLocation.Y, TargetLocation.Z);
}

void AGun::BeginPlay()
{
	Super::BeginPlay();

	GlobalStartLocation = GetActorLocation();

	GetWorld()->GetTimerManager().SetTimer(DestroyTimer, this, &ThisClass::HandleDestruction, 1.f, true, 0.f);
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HasAuthority())
	{
		FVector Location = GetActorLocation();
		float JourneyLength = (GlobalTargetLocation - GlobalStartLocation).Size();
		float JourneyTravalled = (Location - GlobalStartLocation).Size();

		if (JourneyTravalled >= JourneyLength)
		{
			FVector Swap = GlobalStartLocation;
			GlobalStartLocation = GlobalTargetLocation;
			GlobalTargetLocation = Swap;
		}
		FVector Direction = (GlobalTargetLocation - GlobalStartLocation).GetSafeNormal();
		Location += Speed * DeltaTime * Direction;

		SetActorLocation(Location);
	}
}

void AGun::HandleDestruction()
{
	--Time;

	if (Time <= 0)
	{
		GetWorld()->GetTimerManager().ClearTimer(DestroyTimer);
		Destroy(true);


	}
}

