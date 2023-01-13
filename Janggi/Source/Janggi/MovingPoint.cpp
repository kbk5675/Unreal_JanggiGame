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
	// 1. 원래 있었던 타일의 TileIsEmpty false 처리
	// 2. 이동한 현재 타일의 TileIsEmpty true  처리
	// 3. 원래 있었던 타일의 CurrentUnit null  처리
	// 3. 이동한 현재 타일의 CurrentUnit 변경
	// 4. 장기말 위치 변경
	// 5. 장기말의 CurrentTile 변경
	// 6. 장기말의 현재 좌표 변경 

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

