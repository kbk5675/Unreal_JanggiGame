// Fill out your copyright notice in the Description page of Project Settings.


#include "JanggiPlayerController.h"
#include "JanggiGameStateBase.h"
#include "JanggiGameInstance.h"
#include "MovingPoint.h"
#include "BlankTile.h"
#include "MenuSystem/LobbyMenu.h"

void AJanggiPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Call PlayerController"));
	bEnableClickEvents = true;

	World = GetWorld();
	if (!ensure(World != nullptr)) return;
}

void AJanggiPlayerController::ServerClientReady_Implementation()
{
	auto GameState = Cast<AJanggiGameStateBase>(World->GetGameState());
	if (GameState)
	{
		GameState->ClientReady();
	}
}

void AJanggiPlayerController::ServerClientNotReady_Implementation()
{
	auto GameState = Cast<AJanggiGameStateBase>(World->GetGameState());
	if (GameState)
	{
		GameState->ClientNotReady();
	}
}

void AJanggiPlayerController::ServerSetVisibleWaitWidget_Implementation()
{
	auto GameInstance = Cast<UJanggiGameInstance>(GetWorld()->GetGameInstance());

	auto LobbyMenu = Cast<ULobbyMenu>(GameInstance->LobbyMenu);

	LobbyMenu->SetVisibleWaitWidget();
}

void AJanggiPlayerController::ServerSetHiddenWaitWidget_Implementation()
{
	auto GameInstance = Cast<UJanggiGameInstance>(GetWorld()->GetGameInstance());

	auto LobbyMenu = Cast<ULobbyMenu>(GameInstance->LobbyMenu);

	LobbyMenu->SetHiddenWaitWidget();
}

void AJanggiPlayerController::ServerSetEnabledTrueBtnStart_Implementation()
{
	auto GameInstance = Cast<UJanggiGameInstance>(GetWorld()->GetGameInstance());

	auto LobbyMenu = Cast<ULobbyMenu>(GameInstance->LobbyMenu);

	LobbyMenu->SetEnabledTrueBtnStart();
}

void AJanggiPlayerController::ServerSetEnabledFalseBtnStart_Implementation()
{
	auto GameInstance = Cast<UJanggiGameInstance>(GetWorld()->GetGameInstance());

	auto LobbyMenu = Cast<ULobbyMenu>(GameInstance->LobbyMenu);

	LobbyMenu->SetHiddenWaitWidget();
}

void AJanggiPlayerController::ServerMoveDataToInstance_Implementation()
{
	auto GameState = Cast<AJanggiGameStateBase>(World->GetGameState());
	if (GameState)
	{
		GameState->MoveDataToInstance();
	}
}

void AJanggiPlayerController::ServerSetSelectedUnit_Implementation(AActor* Unit)
{
	auto GameState = Cast<AJanggiGameStateBase>(World->GetGameState());
	if (GameState)
	{
		GameState->SetSelectedUnit(Unit);
	}
}

void AJanggiPlayerController::ServerMoveSelectedUnit_Implementation(AActor* MovingPoint, AActor* Unit)
{
	auto TmpMovingPoint = Cast<AMovingPoint>(MovingPoint);
	if (TmpMovingPoint)
	{
		TmpMovingPoint->MoveSelectedUnit(Unit);
	}
}

void AJanggiPlayerController::ServerSetCurrentTileCurrentUnit_Implementation(AActor* CurrentUnit, AActor* CurrentUnitOfTile)
{
	auto JanggiUnit = Cast<ABasePawn>(CurrentUnit);
	if (JanggiUnit)
	{
		JanggiUnit->SetCurrentTileCurrentUnit(CurrentUnitOfTile);
	}
}

void AJanggiPlayerController::ServerSetPosY_Implementation(AActor* Unit, int Y)
{
	auto JanggiUnit = Cast<ABasePawn>(Unit);
	if (JanggiUnit)
	{
		JanggiUnit->SetPosY(Y);
	}
}

void AJanggiPlayerController::ServerSetPosX_Implementation(AActor* Unit, int X)
{
	auto JanggiUnit = Cast<ABasePawn>(Unit);
	if (JanggiUnit)
	{
		JanggiUnit->SetPosX(X);
	}
}

void AJanggiPlayerController::ServerSetVisibleMovingPoint_Implementation(AActor* MovingPoint, bool bVal)
{
	ClientSetVisibleMovingPoint(MovingPoint, bVal);
}

void AJanggiPlayerController::ClientSetVisibleMovingPoint_Implementation(AActor* MovingPoint, bool bVal)
{
	auto GameState = Cast<AJanggiGameStateBase>(World->GetGameState());
	if (GameState)
	{
		GameState->SetVisibleMovingPoint(MovingPoint, bVal);
	}
}

void AJanggiPlayerController::ServerSetCurrentTile_Implementation(AActor* Unit, AActor* Tile)
{
	auto JanggiUnit = Cast<ABasePawn>(Unit);
	if (JanggiUnit)
	{
		auto BlankTile = Cast<ABlankTile>(Tile);
		if (BlankTile)
		{
			JanggiUnit->SetCurrentTile(BlankTile);
		}
	}
}

void AJanggiPlayerController::ServerSetCurrentUnit_Implementation(AActor* Tile, AActor* Unit)
{
	ABlankTile* BlankTile = Cast<ABlankTile>(Tile);
	if (BlankTile)
	{
		BlankTile->SetCurrentUnit(Unit);
	}
}

void AJanggiPlayerController::ServerAttack_Implementation(AActor* SelectedUnit, AActor* TargetUnit)
{
	ABasePawn* SU = Cast<ABasePawn>(SelectedUnit);
	ABasePawn* TU = Cast<ABasePawn>(TargetUnit);
	if (SU && TU)
	{
		SU->Attack(TU);
	}
}

void AJanggiPlayerController::ServerMovingPointHandleDestruction_Implementation(AActor* MovingPoint)
{
	AMovingPoint* MP = Cast<AMovingPoint>(MovingPoint);
	if (MP)
	{
		MP->HandleDestruction();
	}
}

void AJanggiPlayerController::ServerSetHP_Implementation(AActor* Unit, int HP)
{
	ABasePawn* BasePawn = Cast<ABasePawn>(Unit);
	if (BasePawn)
	{
		BasePawn->SetHP(HP);
	}
}

void AJanggiPlayerController::ServerMoveUnit_Implementation(AActor* MovingPoint, AActor* Unit)
{
	AMovingPoint* MP = Cast<AMovingPoint>(MovingPoint);
	if (MP)
	{
		MP->MoveUnit(Unit);
	}
	
}

void AJanggiPlayerController::ServerBasePawnHandleDestruction_Implementation(AActor* Unit)
{
	MulticastBasePawnHandleDestruction(Unit);
}

void AJanggiPlayerController::MulticastBasePawnHandleDestruction_Implementation(AActor* Unit)
{
	ABasePawn* BasePawn = Cast<ABasePawn>(Unit);
	if (BasePawn)
	{
		BasePawn->HandleDestruction();
	}
}
