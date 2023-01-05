// Fill out your copyright notice in the Description page of Project Settings.


#include "JanggiPlayerState.h"
#include "Net/UnrealNetwork.h"

AJanggiPlayerState::AJanggiPlayerState()
{
	PlayerScore = 0;
}

int AJanggiPlayerState::GetPlayerScore() const
{
	return PlayerScore;
}

void AJanggiPlayerState::InitPlayerData()
{
	PlayerScore = 0;
}

void AJanggiPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

}
