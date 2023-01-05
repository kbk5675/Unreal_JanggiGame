// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingActor.generated.h"

UCLASS()
class JANGGI_API AMovingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AMovingActor();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:	

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess))
	float Timer;
};
