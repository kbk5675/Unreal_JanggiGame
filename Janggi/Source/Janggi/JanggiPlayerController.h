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
	/*----------UserWidget-------------*/
	UFUNCTION(Server, Reliable)
	void ServerClientReady();

	UFUNCTION(Server, Reliable)
	void ServerClientNotReady();

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



	/*----------GameState-------------*/
	UFUNCTION(Server, Reliable)
	void ServerSetSelectedUnit(AActor* Unit);

	UFUNCTION(Server, Reliable)
	void ServerSetVisibleMovingPoint(AActor* MovingPoint, bool bVal);

	UFUNCTION(Client, Reliable)
	void ClientSetVisibleMovingPoint(AActor* MovingPoint, bool bVal);


	/*----------MovingPoint.h-------------*/
	UFUNCTION(Server, Reliable)
	void ServerMoveSelectedUnit(AActor* MovingPoint, AActor* Unit);
	
	UFUNCTION(Server, Reliable)
	void ServerSetCurrentUnit(AActor* Tile, AActor* Unit);

	UFUNCTION(Server, Reliable)
	void ServerAttack(AActor* SelectedUnit, AActor* TargetUnit);

	UFUNCTION(Server, Reliable)
	void ServerMoveUnit(AActor* MovingPoint, AActor* Unit);

	UFUNCTION(Server, Reliable)
	void ServerMovingPointHandleDestruction(AActor* MovingPoint);


	/*----------BlankTile.h-------------*/
	

	/*----------BasePawn.h-------------*/
	UFUNCTION(Server, Reliable)
	void ServerSetCurrentTileCurrentUnit(AActor* CurrentUnit, AActor* CurrentUnitOfTile);

	UFUNCTION(Server, Reliable)
	void ServerSetCurrentTile(AActor* Unit, AActor* Tile);

	UFUNCTION(Server, Reliable)
	void ServerSetPosY(AActor* Unit, int Y);

	UFUNCTION(Server, Reliable)
	void ServerSetPosX(AActor* Unit, int X);

	UFUNCTION(Server, Reliable)
	void ServerSetHP(AActor* Unit, int HP);

	UFUNCTION(Server, Reliable)
	void ServerBasePawnHandleDestruction(AActor* Unit);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastBasePawnHandleDestruction(AActor* Unit);

protected:
};
