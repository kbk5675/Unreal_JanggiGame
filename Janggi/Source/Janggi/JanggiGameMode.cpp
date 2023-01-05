// Copyright Epic Games, Inc. All Rights Reserved.

#include "JanggiGameMode.h"
#include "JanggiCharacter.h"
#include "JanggiPlayerState.h"
#include "JanggiPlayerController.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"

AJanggiGameMode::AJanggiGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}

void AJanggiGameMode::PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	Super::PreLogin(OptionsString, Address, UniqueId, ErrorMessage);

	if (GetNumPlayers() >= 2)
	{
		ErrorMessage = TEXT("SERVER IS FULL");
	}
}

void AJanggiGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

}
