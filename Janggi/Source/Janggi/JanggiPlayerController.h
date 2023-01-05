// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "JanggiPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class JANGGI_API AJanggiPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UWorld* World;

	virtual void BeginPlay() override;

	UFUNCTION(Server, Reliable)
	void ServerClientReady();
	void ServerClientReady_Implementation();

	UFUNCTION(Server, Reliable)
	void ServerClientNotReady();
	void ServerClientNotReady_Implementation();

protected:

};
