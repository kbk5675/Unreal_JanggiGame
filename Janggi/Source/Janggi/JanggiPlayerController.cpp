// Fill out your copyright notice in the Description page of Project Settings.


#include "JanggiPlayerController.h"
#include "JanggiGameStateBase.h"

void AJanggiPlayerController::BeginPlay()
{
	Super::BeginPlay();

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




