// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "JanggiGameMode.generated.h"

UCLASS(minimalapi)
class AJanggiGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AJanggiGameMode();

	virtual void PreLogin(const FString& Options, const FString& Address, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage);
	virtual void PostLogin(APlayerController* NewPlayer);
};



