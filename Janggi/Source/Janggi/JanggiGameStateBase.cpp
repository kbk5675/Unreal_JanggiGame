// Fill out your copyright notice in the Description page of Project Settings.


#include "JanggiGameStateBase.h"
#include "JanggiGameInstance.h"
#include "JanggiPlayerController.h"
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
	DOREPLIFETIME(ThisClass, Turn); 
	DOREPLIFETIME(ThisClass, TableType);
}

void AJanggiGameStateBase::UpdateServerTimeSeconds()
{
	Super::UpdateServerTimeSeconds();
}

void AJanggiGameStateBase::OnRep_MoveDataToInstance()
{
	auto GameInstance = Cast<UJanggiGameInstance>(GetWorld()->GetGameInstance());
	GameInstance->TableType = this->TableType;

	auto Controller = Cast<AJanggiPlayerController>(GetWorld()->GetFirstPlayerController());
	Controller->ServerMoveDataToInstance();
}

void AJanggiGameStateBase::MoveDataToInstance()
{
	auto GameInstance = Cast<UJanggiGameInstance>(GetWorld()->GetGameInstance());
	GameInstance->TableType = this->TableType;
}


