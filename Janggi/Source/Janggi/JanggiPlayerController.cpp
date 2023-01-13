// Fill out your copyright notice in the Description page of Project Settings.


#include "JanggiPlayerController.h"
#include "JanggiGameStateBase.h"
#include "JanggiGameInstance.h"
#include "MenuSystem/LobbyMenu.h"

void AJanggiPlayerController::BeginPlay()
{
	Super::BeginPlay();
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

void AJanggiPlayerController::ServerSetTableType_Implementation(int Val)
{
	auto GameState = Cast<AJanggiGameStateBase>(World->GetGameState());
	if (GameState)
	{
		GameState->SetTableType(Val);
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
