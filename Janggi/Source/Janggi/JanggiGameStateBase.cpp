// Fill out your copyright notice in the Description page of Project Settings.


#include "JanggiGameStateBase.h"
#include "JanggiGameInstance.h"
#include "JanggiPlayerController.h"
#include "Net/UnrealNetwork.h"

AJanggiGameStateBase::AJanggiGameStateBase()
{
	PrimaryActorTick.bCanEverTick = true;
	UE_LOG(LogTemp, Warning, TEXT("Call GameStateBase"));
}

void AJanggiGameStateBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	auto GameInstance = Cast<UJanggiGameInstance>(GetWorld()->GetGameInstance());
	if (GameInstance)
	{
		int Temp = GameInstance->TableType;
		this->TableType = Temp;
	}
}

void AJanggiGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ThisClass, bClientReady);
	DOREPLIFETIME(ThisClass, SelectedUnit);
	DOREPLIFETIME(ThisClass, BoardTiles);
	DOREPLIFETIME(ThisClass, MovingPoints);
	DOREPLIFETIME(ThisClass, Time);
	DOREPLIFETIME(ThisClass, Turn); 
}

void AJanggiGameStateBase::MoveDataToInstance()
{
	auto GameInstance = Cast<UJanggiGameInstance>(GetWorld()->GetGameInstance());
	GameInstance->TableType = this->TableType;
}

void AJanggiGameStateBase::FindMoveableTile(int TargetPosY, int TargetPosX)
{
	for (int i = 0; i < BoardTiles.Num(); i++)
	{
		auto TargetTile = Cast<ABlankTile>(BoardTiles[i]);

		if (TargetTile->GetTileInfo().Y == TargetPosY && TargetTile->GetTileInfo().X == TargetPosX)
		{
			ABasePawn* TargetTileUnit = Cast<ABasePawn>(TargetTile->GetCurrentUnit());
			if (TargetTileUnit)
			{
				if (Cast<ABasePawn>(SelectedUnit)->GetTeam() == TargetTileUnit->GetTeam())
				{
					return;
				}
				else
				{
					FindMovingPoint(Cast<AActor>(TargetTile));
				}
			}
			else
			{
				FindMovingPoint(Cast<AActor>(TargetTile));
			}
		}
	}
}

void AJanggiGameStateBase::FindMovingPoint(AActor * Tile)
{
	ABlankTile* TargetTile = Cast<ABlankTile>(Tile);

	for (int i = 0; i < MovingPoints.Num(); i++)
	{
		AMovingPoint* TargetMovingPoint = Cast<AMovingPoint>(MovingPoints[i]);

		if (TargetTile->GetTileInfo().Y == TargetMovingPoint->Y && TargetTile->GetTileInfo().X == TargetMovingPoint->X)
		{
			if (HasAuthority())
			{
				SetVisibleMovingPoint(TargetMovingPoint, false);
			}
			else
			{
				auto Controller = Cast<AJanggiPlayerController>(GetWorld()->GetFirstPlayerController());
				Controller->ServerSetVisibleMovingPoint(TargetMovingPoint, false);
			}
		}
	}
}

void AJanggiGameStateBase::SetVisibleMovingPoint(AActor* MovingPoint, bool bVal)
{
	AMovingPoint* TargetMovingPoint = Cast<AMovingPoint>(MovingPoint);
	if (TargetMovingPoint)
	{
		//TargetMovingPoint->SetActorEnableCollision(true);
		TargetMovingPoint->SetActorHiddenInGame(bVal);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Can't Find MovingPoint Actor!"));
	}
}


