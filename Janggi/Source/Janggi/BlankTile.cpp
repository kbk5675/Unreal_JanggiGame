// Fill out your copyright notice in the Description page of Project Settings.


#include "BlankTile.h"
#include "JanggiGameStateBase.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

ABlankTile::ABlankTile()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root Scene"));
	RootComponent = SceneComponent;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);
	BaseMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	UnitSlot = CreateDefaultSubobject<USceneComponent>(TEXT("Unit Slot"));
	UnitSlot->SetupAttachment(RootComponent);
	UnitSlot->SetRelativeLocation(FVector(60.f, 65.f, 15.f));
	
	static ConstructorHelpers::FClassFinder<AActor>MovingPointBPClass(TEXT("/Game/Blueprints/BP_MovingPoint"));
	if (MovingPointBPClass.Succeeded())
	{
		MovingPointClass = MovingPointBPClass.Class;
	}
}

void ABlankTile::BeginPlay()
{
	Super::BeginPlay();

	SpawnActors();
}

void ABlankTile::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, TileInfo);
	DOREPLIFETIME(ThisClass, CurrentUnit);
	DOREPLIFETIME(ThisClass, CurrentMovingPoint);
}


void ABlankTile::SpawnActors()
{	
	ABasePawn* Unit;
	AMovingPoint* MovingPoint;

	FVector Location = UnitSlot->GetComponentLocation();
	FRotator Rotation = UnitSlot->GetComponentRotation();

	if (HasAuthority())
	{// Only Once Spawn In Server
		if (SpawnUnitClass)
		{
			Unit = GetWorld()->SpawnActor<ABasePawn>(SpawnUnitClass, Location, Rotation);
			if (Unit)
			{
				SetCurrentUnit(Unit);
				Unit->SetCurrentTileAndPos(this);
			}
		}

		if (MovingPointClass)
		{
			MovingPoint = GetWorld()->SpawnActor<AMovingPoint>(MovingPointClass, Location, Rotation);
			if (MovingPoint)
			{
				SetCurrentMovingPoint(MovingPoint);
				CurrentMovingPoint->CurrentTile = this;
				CurrentMovingPoint->Y = this->GetTileInfo().Y;
				CurrentMovingPoint->X = this->GetTileInfo().X;
				//CurrentMovingPoint->SetActorEnableCollision(false);
				CurrentMovingPoint->SetActorHiddenInGame(true);

				auto GameState = Cast<AJanggiGameStateBase>(GetWorld()->GetGameState());
				GameState->MovingPoints.Add(MovingPoint);
			}
		}
	}
}

void ABlankTile::SetCurrentUnit(AActor* Unit)
{
	auto Temp = Cast<ABasePawn>(Unit);
	CurrentUnit = Temp;
}




