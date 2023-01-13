// Fill out your copyright notice in the Description page of Project Settings.


#include "Jole.h"
#include "../JanggiGameStateBase.h"
#include "../BlankTile.h"

AJole::AJole()
{
	HP = 100;
	Damage = 20;
	Move = 1;
	UnitScore = 2;

	BaseMesh->OnClicked.AddDynamic(this, &ThisClass::OnClickJole);
}

void AJole::BeginPlay()
{
	// Create Level after
	UE_LOG(LogTemp, Warning, TEXT("Jole BeginPlay"));
}

void AJole::OnClickJole(UPrimitiveComponent* ClickedComp, FKey ButtonClicked)
{
	FoundMovableTile();
}

void AJole::FoundMovableTile()
{
	auto GameState = Cast<AJanggiGameStateBase>(GetWorld()->GetGameState());

	for (int i = 0; i < GameState->BoardTiles.Num(); i++)
	{
		auto Tile = Cast<ABlankTile>(GameState->BoardTiles[i]);

		int TargetPosY = Tile->GetTileInfo().Y;
		int TargetPosX = Tile->GetTileInfo().X;
		
		auto TargetTileUnit = Cast<ABasePawn>(Tile->GetCurrentUnit());
		
		if (Team == 1)
		{
			if (TargetPosY == this->Y + 1 && TargetPosX == this->X)
			{
					Tile->SpawnMovePoint(this->Team);
			}
		}
		else
		{
			if (TargetPosY == this->Y - 1 && TargetPosX == this->X)
			{
				
					Tile->SpawnMovePoint(this->Team);
			}
		}
		
		if (TargetPosY == this->Y && TargetPosX == this->X + 1)
		{
			
				Tile->SpawnMovePoint(this->Team);
			
		}
		if (TargetPosY == this->Y && TargetPosX == this->X - 1)
		{
			
				Tile->SpawnMovePoint(this->Team);
			
		}
	}
}





