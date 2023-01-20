// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlankTile.h"
#include "GameFramework/GameStateBase.h"
#include "JanggiGameStateBase.generated.h"

/**
 * 
 */
enum ETURN 
{
	Server_Turn = 0,
	Client_Turn = 1,
};

UCLASS()
class JANGGI_API AJanggiGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	AJanggiGameStateBase();
	virtual void PostInitializeComponents() override;
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const;

	bool GetbClientReady() { return bClientReady; }
	bool IsClientReady() { return bClientReady; }

	void  ClientReady() { bClientReady = true; }
	void  ClientNotReady() { bClientReady = false; }

	void IncreaseTime(float const Value) { Time += Value; }
	void CountDownTime(float const Value) { Time -= Value; }

	void	SetSelectedUnit(AActor* Unit) { SelectedUnit = Unit; }
	AActor* GetSelectedUnit() { return SelectedUnit; }

	void	SetTableType(int Val) { TableType = Val; }
	int		GetTableType() { return TableType; }

	void MoveDataToInstance();
	void FindMoveableTile(int TargetPosY,int TargetPosX);
	void FindMovingPoint(AActor* Tile);
	void SetVisibleMovingPoint(AActor* MovingPoint, bool bVal);

	UPROPERTY(Replicated)
	TArray<class ABlankTile*> BoardTiles;

	UPROPERTY(Replicated)
	TArray<class AMovingPoint*> MovingPoints;


	
protected:
	
private:
	UPROPERTY(Replicated)
	bool bClientReady = false;

	UPROPERTY(Replicated)
	int	Turn = 0;

	UPROPERTY(Replicated)
	class AActor* SelectedUnit;

	UPROPERTY(Replicated)
	float Time = 120.f;

	int	TableType = 0;
};
