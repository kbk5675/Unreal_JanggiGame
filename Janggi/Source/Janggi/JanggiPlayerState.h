// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "JanggiPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class JANGGI_API AJanggiPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	AJanggiPlayerState();

	int GetPlayerScore() const;
	
	void InitPlayerData();

protected:

	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const override;

	UPROPERTY(Transient)
	int PlayerScore;
};
