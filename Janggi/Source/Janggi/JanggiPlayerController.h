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

	UFUNCTION(Server, Reliable)
	void ServerClientNotReady();

	UFUNCTION(Server, Reliable)
	void ServerSetTableType(int Val);

	UFUNCTION(Server, Reliable)
	void ServerSetVisibleWaitWidget();

	UFUNCTION(Server, Reliable)
	void ServerSetHiddenWaitWidget();

	UFUNCTION(Server, Reliable)
	void ServerSetEnabledTrueBtnStart();

	UFUNCTION(Server, Reliable)
	void ServerSetEnabledFalseBtnStart();

	UFUNCTION(Server, Reliable)
	void ServerMoveDataToInstance();

protected:

};
