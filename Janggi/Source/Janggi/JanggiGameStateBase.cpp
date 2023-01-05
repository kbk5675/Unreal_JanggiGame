// Fill out your copyright notice in the Description page of Project Settings.


#include "JanggiGameStateBase.h"
#include "Net/UnrealNetwork.h"

AJanggiGameStateBase::AJanggiGameStateBase()
{
	PrimaryActorTick.bCanEverTick = true;
	UE_LOG(LogTemp, Warning, TEXT("AJanggiGameStateBase"));
}

void AJanggiGameStateBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, bClientReady);
	DOREPLIFETIME(ThisClass, Time);
}

void AJanggiGameStateBase::UpdateServerTimeSeconds()
{
	Super::UpdateServerTimeSeconds();
}

