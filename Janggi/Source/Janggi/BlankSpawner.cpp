// Fill out your copyright notice in the Description page of Project Settings.


#include "BlankSpawner.h"
#include "Kismet/GameplayStatics.h"

ABlankSpawner::ABlankSpawner()
{
	PrimaryActorTick.bCanEverTick = true;
	SectorSize = 120.f;
	
	// Base
	static ConstructorHelpers::FClassFinder<ABlankTile> TileBPClass(TEXT("/Game/Blueprints/Tile/BP_Tile"));
	if (TileBPClass.Succeeded())
	{
		TileClass = TileBPClass.Class;
	}

	// King
	static ConstructorHelpers::FClassFinder<ABlankTile> KingTileBPClass(TEXT("/Game/Blueprints/Tile/BP_KingTile"));
	if (KingTileBPClass.Succeeded())
	{
		KingTileClass = KingTileBPClass.Class;
	}

	// Cha
	static ConstructorHelpers::FClassFinder<ABlankTile> ChaTileBPClass(TEXT("/Game/Blueprints/Tile/BP_ChaTile"));
	if (ChaTileBPClass.Succeeded())
	{
		ChaTileClass = ChaTileBPClass.Class;
	}
	
	// Jole
	static ConstructorHelpers::FClassFinder<ABlankTile> JoleTileBPClass(TEXT("/Game/Blueprints/Tile/BP_JoleTile"));
	if (JoleTileBPClass.Succeeded())
	{
		JoleTileClass = JoleTileBPClass.Class;
	}

	// Ma
	static ConstructorHelpers::FClassFinder<ABlankTile> MaTileBPClass(TEXT("/Game/Blueprints/Tile/BP_MaTile"));
	if (MaTileBPClass.Succeeded())
	{
		MaTileClass = MaTileBPClass.Class;
	}

	// Pho
	static ConstructorHelpers::FClassFinder<ABlankTile> PhoTileBPClass(TEXT("/Game/Blueprints/Tile/BP_PhoTile"));
	if (PhoTileBPClass.Succeeded())
	{
		PhoTileClass = PhoTileBPClass.Class;
	}

	// Sa
	static ConstructorHelpers::FClassFinder<ABlankTile> SaTileBPClass(TEXT("/Game/Blueprints/Tile/BP_SaTile"));
	if (SaTileBPClass.Succeeded())
	{
		SaTileClass = SaTileBPClass.Class;
	}

	// Sang
	static ConstructorHelpers::FClassFinder<ABlankTile> SangTileBPClass(TEXT("/Game/Blueprints/Tile/BP_SangTile"));
	if (SangTileBPClass.Succeeded())
	{
		SangTileClass = SangTileBPClass.Class;
	}
}

void ABlankSpawner::BeginPlay()
{
	Super::BeginPlay();
	
	BuildBoard(FVector(0.f, 0.f, 0.f), 9, 10);
}

void ABlankSpawner::BuildBoard(const FVector CenteredLocation, const int X, const int Y)
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

				if (TileClass)
				{
					AActor* TileToSpawn;

					if ((OuterIndex == 1 && InnerIndex == 4) || (OuterIndex == 8 && InnerIndex == 4))
					{	// King
						TileToSpawn = UGameplayStatics::BeginDeferredActorSpawnFromClass(
							this, KingTileClass.LoadSynchronous(), SpawnTransform);
					}
					else if ((OuterIndex == 0 && InnerIndex == 0) || (OuterIndex == 0 && InnerIndex == 8) || 
							 (OuterIndex == 9 && InnerIndex == 0) || (OuterIndex == 9 && InnerIndex == 8))
					{	// Cha
						TileToSpawn = UGameplayStatics::BeginDeferredActorSpawnFromClass(
							this, ChaTileClass.LoadSynchronous(), SpawnTransform);
					}
					else if ((OuterIndex == 0 && InnerIndex == 1) || (OuterIndex == 0 && InnerIndex == 7) ||
							 (OuterIndex == 9 && InnerIndex == 1) || (OuterIndex == 9 && InnerIndex == 7))
					{	// Sang
						TileToSpawn = UGameplayStatics::BeginDeferredActorSpawnFromClass(
							this, SangTileClass.LoadSynchronous(), SpawnTransform);
					}
					else if ((OuterIndex == 0 && InnerIndex == 2) || (OuterIndex == 0 && InnerIndex == 6) ||
						(OuterIndex == 9 && InnerIndex == 2) || (OuterIndex == 9 && InnerIndex == 6))
					{	// Ma
						TileToSpawn = UGameplayStatics::BeginDeferredActorSpawnFromClass(
							this, MaTileClass.LoadSynchronous(), SpawnTransform);
					}
					else if ((OuterIndex == 0 && InnerIndex == 3) || (OuterIndex == 0 && InnerIndex == 5) ||
						(OuterIndex == 9 && InnerIndex == 3) || (OuterIndex == 9 && InnerIndex == 5))
					{	// Sa
						TileToSpawn = UGameplayStatics::BeginDeferredActorSpawnFromClass(
							this, SaTileClass.LoadSynchronous(), SpawnTransform);
					}
					else if ((OuterIndex == 2 && InnerIndex == 1) || (OuterIndex == 2 && InnerIndex == 7) ||
						(OuterIndex == 7 && InnerIndex == 1) || (OuterIndex == 7 && InnerIndex == 7))
					{	// Pho
						TileToSpawn = UGameplayStatics::BeginDeferredActorSpawnFromClass(
							this, PhoTileClass.LoadSynchronous(), SpawnTransform);
					}
					else if ((OuterIndex == 3 && InnerIndex == 0) || (OuterIndex == 3 && InnerIndex == 2) ||
							 (OuterIndex == 3 && InnerIndex == 4) || (OuterIndex == 3 && InnerIndex == 6) ||
							 (OuterIndex == 3 && InnerIndex == 8) || 
							 (OuterIndex == 6 && InnerIndex == 0) || (OuterIndex == 6 && InnerIndex == 2) ||
							 (OuterIndex == 6 && InnerIndex == 4) || (OuterIndex == 6 && InnerIndex == 6) ||
							 (OuterIndex == 6 && InnerIndex == 8))
					{	// Jole
						TileToSpawn = UGameplayStatics::BeginDeferredActorSpawnFromClass(
							this, JoleTileClass.LoadSynchronous(), SpawnTransform);
					}
					else
					{
						TileToSpawn = UGameplayStatics::BeginDeferredActorSpawnFromClass(
							this, TileClass.LoadSynchronous(), SpawnTransform);
					}

					ABlankTile* Tile = Cast<ABlankTile>(TileToSpawn);
					if (!ensure(Tile != nullptr)) return;

					Tile->SetTileInfo(FBlankTileInfo(InnerIndex, OuterIndex, 0));
					
					TileToSpawn->FinishSpawning(SpawnTransform);
					
					BoardTiles.Add(TileToSpawn);
					TileToSpawn->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform);

				}
			}
		}
	}
}

void ABlankSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

