// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Jole.generated.h"

/**
 * 
 */
UCLASS()
class JANGGI_API AJole : public ABasePawn
{
	GENERATED_BODY()

protected:
	AJole();
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnClickJole(UPrimitiveComponent* ClickedComp, FKey ButtonClicked);
};
