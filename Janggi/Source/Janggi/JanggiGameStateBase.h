// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlankTile.h"
#include "GameFramework/GameStateBase.h"
#include "JanggiGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class JANGGI_API AJanggiGameStateBase : public AGameStateBase
{
	GENERATED_BODY()

public:
	AJanggiGameStateBase();
	virtual void GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const;
	virtual void UpdateServerTimeSeconds() override;

	bool GetbClientReady() { return bClientReady; }
	bool IsClientReady() { return bClientReady; }

	void  ClientReady() { bClientReady = true; }
	void  ClientNotReady() { bClientReady = false; }

	float GetTime() { return Time; }

	void IncreaseTime(float Value) { Time += Value; }
	void CountDownTime(float Value) { Time -= Value; }

	void	SetSelectedUnit(AActor* Unit) { SelectedUnit = Unit; }
	AActor* GetSelectedUnit() { return SelectedUnit; }

	void	SetTableType(int Val) { TableType = Val; }
	int		GetTableType() { return TableType; }

	UFUNCTION()
	void OnRep_MoveDataToInstance();
	void MoveDataToInstance();

	UPROPERTY(VisibleAnywhere)
	TArray<class ABlankTile*> BoardTiles;
	
protected:
	

private:
	UPROPERTY(VisibleAnywhere, Replicated)
	bool	bClientReady = false;

	UPROPERTY(VisibleAnywhere, Replicated)
	float	Time = 120.f;

	UPROPERTY(VisibleAnywhere, Replicated)
	bool	Turn = 0;

	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_MoveDataToInstance)
	int		TableType = 0;

	UPROPERTY(VisibleAnywhere)
	class AActor* SelectedUnit;

	
};
