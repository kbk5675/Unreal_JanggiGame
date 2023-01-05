// Fill out your copyright notice in the Description page of Project Settings.


#include "BlankTile.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"

ABlankTile::ABlankTile()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Scene"));
	RootComponent = SceneComponent;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);

	UnitSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Unit Spawn Point"));
	UnitSpawnPoint->SetupAttachment(RootComponent);
	UnitSpawnPoint->SetRelativeLocation(FVector(60.f, 65.f, 20.f));

}

void ABlankTile::BeginPlay()
{
	Super::BeginPlay();

	FVector Location = UnitSpawnPoint->GetComponentLocation();
	FRotator Rotation = UnitSpawnPoint->GetComponentRotation();

	auto Unit =
		GetWorld()->SpawnActor<ABasePawn>(UnitClass, Location, Rotation);
}

