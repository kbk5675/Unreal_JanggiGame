// Fill out your copyright notice in the Description page of Project Settings.


#include "BlankSpawner.h"
#include "JanggiGameStateBase.h"
#include "JanggiGameInstance.h"
#include "Kismet/GameplayStatics.h"

ABlankSpawner::ABlankSpawner()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	SectorSize = 120.f;
}

void ABlankSpawner::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		auto GameState = Cast<AJanggiGameStateBase>(GetWorld()->GetGameState());
		if (GameState)
		{
			int Temp = GameState->GetTableType();

			switch (Temp)
			{
			case 0:	// 마상마상
				BuildBoard(FVector(0.f, 0.f, 5.f), 9, 10, TableType1);
				break;
			case 1: // 마상마상
				BuildBoard(FVector(0.f, 0.f, 5.f), 9, 10, TableType1);
				break;
			case 2: // 상마상마
				BuildBoard(FVector(0.f, 0.f, 5.f), 9, 10, TableType2);
				break;
			case 3: // 마마상상
				BuildBoard(FVector(0.f, 0.f, 5.f), 9, 10, TableType3);
				break;
			case 4: // 상상마마
				BuildBoard(FVector(0.f, 0.f, 5.f), 9, 10, TableType4);
				break;
			}
		}
	}
}
	

void ABlankSpawner::BuildBoard(const FVector CenteredLocation, const int X, const int Y, const TArray<int> TableType)
{
	// Do not execute if BoardTiles array already contains Tiles
	if(BoardTiles.Num() == 0)
	{
		BoardSize.X = X;
		BoardSize.Y = Y;

		// 2D Grid Execution Macro, rewritten to C++
		for (auto OuterIndex{ 0 }; OuterIndex <= Y - 1; ++OuterIndex)
		{
			for (auto InnerIndex{ 0 }; InnerIndex <= X - 1; ++InnerIndex)
			{
				// Prepare a Spawn Transform
				FVector SpawnLocation =
					FVector(
						static_cast<float>(InnerIndex) - static_cast<float>(X) / 2.f,
						static_cast<float>(OuterIndex) - static_cast<float>(Y) / 2.f,
						0.f) 
					* SectorSize
					* 1.f 
					+ CenteredLocation;

				FTransform SpawnTransform;
				SpawnTransform.SetLocation(SpawnLocation);

				AActor* TileToSpawn;

				if ((OuterIndex == 1 && InnerIndex == 4))
				{	// King Red
					TileToSpawn = UGameplayStatics::BeginDeferredActorSpawnFromClass(this, KingRedTileClass.LoadSynchronous(), SpawnTransform);
				}
				else if ((OuterIndex == 8 && InnerIndex == 4))
				{	// King Blue
					TileToSpawn = UGameplayStatics::BeginDeferredActorSpawnFromClass(this, KingBlueTileClass.LoadSynchronous(), SpawnTransform);
				}
				else if ((OuterIndex == TableType[0] && InnerIndex == TableType[1]) || (OuterIndex == TableType[2] && InnerIndex == TableType[3]))
				{	// Sang Red
					TileToSpawn = UGameplayStatics::BeginDeferredActorSpawnFromClass(this, SangRedTileClass.LoadSynchronous(), SpawnTransform);
				}
				else if ((OuterIndex == TableType[4] && InnerIndex == TableType[5]) || (OuterIndex == TableType[6] && InnerIndex == TableType[7]))
				{	// Sang Blue
					TileToSpawn = UGameplayStatics::BeginDeferredActorSpawnFromClass(this, SangBlueTileClass.LoadSynchronous(), SpawnTransform);
				}
				else if ((OuterIndex == TableType[8] && InnerIndex == TableType[9]) || (OuterIndex == TableType[10] && InnerIndex == TableType[11]))
				{	// Ma Red
					TileToSpawn = UGameplayStatics::BeginDeferredActorSpawnFromClass(this, MaRedTileClass.LoadSynchronous(), SpawnTransform);
				}
				else if ((OuterIndex == TableType[12] && InnerIndex == TableType[13]) || (OuterIndex == TableType[14] && InnerIndex == TableType[15]))
				{	// Ma Blue
					TileToSpawn = UGameplayStatics::BeginDeferredActorSpawnFromClass(this, MaBlueTileClass.LoadSynchronous(), SpawnTransform);
				}
				else if ((OuterIndex == 0 && InnerIndex == 0) || (OuterIndex == 0 && InnerIndex == 8))
				{	// Cha Red
					TileToSpawn = UGameplayStatics::BeginDeferredActorSpawnFromClass(this, ChaRedTileClass.LoadSynchronous(), SpawnTransform);
				}
				else if ((OuterIndex == 9 && InnerIndex == 0) || (OuterIndex == 9 && InnerIndex == 8))
				{	// Cha Blue
					TileToSpawn = UGameplayStatics::BeginDeferredActorSpawnFromClass(this, ChaBlueTileClass.LoadSynchronous(), SpawnTransform);
				}
				else if ((OuterIndex == 0 && InnerIndex == 3) || (OuterIndex == 0 && InnerIndex == 5))
				{	// Sa Red
					TileToSpawn = UGameplayStatics::BeginDeferredActorSpawnFromClass(this, SaRedTileClass.LoadSynchronous(), SpawnTransform);
				}
				else if ((OuterIndex == 9 && InnerIndex == 3) || (OuterIndex == 9 && InnerIndex == 5))
				{	// Sa Blue
					TileToSpawn = UGameplayStatics::BeginDeferredActorSpawnFromClass(this, SaBlueTileClass.LoadSynchronous(), SpawnTransform);
				}
				else if ((OuterIndex == 2 && InnerIndex == 1) || (OuterIndex == 2 && InnerIndex == 7))
				{	// Pho Red
					TileToSpawn = UGameplayStatics::BeginDeferredActorSpawnFromClass(this, PhoRedTileClass.LoadSynchronous(), SpawnTransform);
				}
				else if ((OuterIndex == 7 && InnerIndex == 1) || (OuterIndex == 7 && InnerIndex == 7))
				{	// Pho Blue
					TileToSpawn = UGameplayStatics::BeginDeferredActorSpawnFromClass(this, PhoBlueTileClass.LoadSynchronous(), SpawnTransform);
				}
				else if ((OuterIndex == 3 && InnerIndex == 0) || (OuterIndex == 3 && InnerIndex == 2) ||
						 (OuterIndex == 3 && InnerIndex == 4) || (OuterIndex == 3 && InnerIndex == 6) ||
						 (OuterIndex == 3 && InnerIndex == 8))
				{	// Jole Red
					TileToSpawn = UGameplayStatics::BeginDeferredActorSpawnFromClass(this, JoleRedTileClass.LoadSynchronous(), SpawnTransform);
				}
				else if ((OuterIndex == 6 && InnerIndex == 0) || (OuterIndex == 6 && InnerIndex == 2) ||
						 (OuterIndex == 6 && InnerIndex == 4) || (OuterIndex == 6 && InnerIndex == 6) ||
						 (OuterIndex == 6 && InnerIndex == 8))
				{	// Jole Blue
					TileToSpawn = UGameplayStatics::BeginDeferredActorSpawnFromClass(this, JoleBlueTileClass.LoadSynchronous(), SpawnTransform);
				}
				else
				{
					TileToSpawn = UGameplayStatics::BeginDeferredActorSpawnFromClass(this, TileClass.LoadSynchronous(), SpawnTransform);

					ABlankTile* Tile = Cast<ABlankTile>(TileToSpawn);
					if (!ensure(Tile != nullptr)) return;

					Tile->SetTileInfo(FBlankTileInfo(InnerIndex, OuterIndex, 0));

					TileToSpawn->FinishSpawning(SpawnTransform);

					BoardTiles.Add(Tile);
					TileToSpawn->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

					continue;
				}

				ABlankTile* Tile = Cast<ABlankTile>(TileToSpawn);
				if (!ensure(Tile != nullptr)) return;

				Tile->SetTileInfo(FBlankTileInfo(InnerIndex, OuterIndex, 0));

				TileToSpawn->FinishSpawning(SpawnTransform);

				BoardTiles.Add(Tile);
				TileToSpawn->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);
			}
		}
	}
	auto GameState = Cast<AJanggiGameStateBase>(GetWorld()->GetGameState());
	GameState->BoardTiles = this->BoardTiles;
}

void ABlankSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

