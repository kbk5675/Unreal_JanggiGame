// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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
	void  ClientReady() { bClientReady = true; }
	void  ClientNotReady() { bClientReady = false; }

	float GetTime() { return Time; }
	void IncreaseTime(float Value) { Time += Value; }
	void CountDownTime(float Value) { Time -= Value; }

	bool IsClientReady() { return bClientReady; }

protected:

private:
	UPROPERTY(VisibleAnywhere, Replicated)
	bool bClientReady = false;

	UPROPERTY(VisibleAnywhere, Replicated)
	float Time = 120.f;
};
