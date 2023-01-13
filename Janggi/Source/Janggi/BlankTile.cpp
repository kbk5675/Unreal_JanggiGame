// Fill out your copyright notice in the Description page of Project Settings.


#include "BlankTile.h"
#include "MovingPoint.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SceneComponent.h"
#include "Kismet/GameplayStatics.h"

ABlankTile::ABlankTile() : bIsSpawnMovingPoint(false)
{
	PrimaryActorTick.bCanEverTick = true;

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

void ABlankTile::SpawnUnit()
{
	FVector Location = UnitSlot->GetComponentLocation();
	FRotator Rotation = UnitSlot->GetComponentRotation();

	ABasePawn* Unit = GetWorld()->SpawnActor<ABasePawn>(SpawnUnitClass, Location, Rotation);
	if (Unit)
	{
		SetCurrentUnit(Unit);
		Unit->SetCurrentTile(this);
	}
}

void ABlankTile::SpawnMovePoint(int const MovingUnitTeamInfo)
{
	// TO Do
	// 1. UnitSlot�� ��ġ, ȸ�� ���� �޾ƿ� SpawnActor�� MovingPointActor�� ����
	// 2. CurrentUnit�� �Ʊ������̸� �������� �ʴ´�.
	// 3. MovingPointActor�� �̹� �����Ǿ� �ִٸ� �� �̻� �������� �ʴ´�.

	FVector Location = UnitSlot->GetComponentLocation();
	FRotator Rotation = UnitSlot->GetComponentRotation();

	if (CurrentUnit)
	{
		if (CurrentUnit->GetTeam() == MovingUnitTeamInfo) return;
	}

	if (!GetbIsSpawnMovingPoint())
	{
		auto MovingPoint = GetWorld()->SpawnActor<AMovingPoint>(MovingPointClass, Location, Rotation);
		if (MovingPoint)
		{
			MovingPoint->CurrentTile = this;
			MovingPoint->Y = this->GetTileInfo().Y;
			MovingPoint->X = this->GetTileInfo().X;
			SetbIsSpawnMovingPoint(true);
		}
	}
}

void ABlankTile::SetCurrentUnit(AActor* Unit)
{
	auto Temp = Cast<ABasePawn>(Unit);
	CurrentUnit = Temp;
}

void ABlankTile::BeginPlay()
{
	Super::BeginPlay();

	SpawnUnit();
}

void ABlankTile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}



