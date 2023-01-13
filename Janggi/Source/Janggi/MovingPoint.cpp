// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPoint.h"
#include "Unit/BasePawn.h"
#include "JanggiGameStateBase.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"

AMovingPoint::AMovingPoint()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = false;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	RootComponent = BaseMesh;
	BaseMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BaseMesh->OnClicked.AddDynamic(this, &ThisClass::OnClickedMovingPoint);

	ClickSound = CreateDefaultSubobject<USoundBase>(TEXT("Click Sound"));
}

void AMovingPoint::BeginPlay()
{
	Super::BeginPlay();

	
}

void AMovingPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMovingPoint::OnClickedMovingPoint(UPrimitiveComponent* ClickedComp, FKey ButtonClicked)
{
	auto GameState = Cast<AJanggiGameStateBase>(GetWorld()->GetGameState());
	if (GameState)
	{
		AActor* MovingUnit = GameState->GetSelectedUnit();
		if (MovingUnit)
		{
			MoveUnit(MovingUnit);
		}
	}
}

void AMovingPoint::MoveUnit(AActor* Unit)
{
	// ToDo
	// 1. ���� �־��� Ÿ���� TileIsEmpty false ó��
	// 2. �̵��� ���� Ÿ���� TileIsEmpty true  ó��
	// 3. ���� �־��� Ÿ���� CurrentUnit null  ó��
	// 3. �̵��� ���� Ÿ���� CurrentUnit ����
	// 4. ��⸻ ��ġ ����
	// 5. ��⸻�� CurrentTile ����
	// 6. ��⸻�� ���� ��ǥ ���� 

	auto JanggiUnit = Cast<ABasePawn>(Unit);
	if (JanggiUnit)
	{
		JanggiUnit->SetCurrentTileIsEmpty(0);
		JanggiUnit->SetCurrentTileCurrentUnit(nullptr);

		this->CurrentTile->SetTileIsEmpty(1);
		this->CurrentTile->SetCurrentUnit(JanggiUnit);

		JanggiUnit->SetActorLocation(this->GetTargetLocation());
		JanggiUnit->SetCurrentTile(this->CurrentTile);
		JanggiUnit->SetPosY(this->Y);
		JanggiUnit->SetPosX(this->X);
	}

	HandleDestruction();
}

void AMovingPoint::HandleDestruction()
{
	if (ClickSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ClickSound, GetActorLocation());
	}

	this->CurrentTile->SetbIsSpawnMovingPoint(false);

	TSubclassOf<AMovingPoint> classToFind;
	classToFind = AMovingPoint::StaticClass();
	TArray<AActor*> FoundMovingPoints;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), classToFind, FoundMovingPoints);

	for (int i = 0; i < FoundMovingPoints.Num(); i++)
	{
		auto MovingPoint = Cast<AMovingPoint>(FoundMovingPoints[i]);
		if (MovingPoint)
		{
			MovingPoint->CurrentTile->SetbIsSpawnMovingPoint(false);
			MovingPoint->Destroy(true);
		}
	}
}

