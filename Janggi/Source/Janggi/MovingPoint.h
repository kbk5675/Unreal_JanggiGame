// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Unit/BasePawn.h"
#include "BlankTile.h"
#include "GameFramework/Actor.h"
#include "MovingPoint.generated.h"

UCLASS()
class JANGGI_API AMovingPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	AMovingPoint();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnClickedMovingPoint(UPrimitiveComponent* ClickedComp, FKey ButtonClicked);

	void MoveUnit(AActor* Unit);
	void HandleDestruction();

	class ABlankTile* CurrentTile;

	UPROPERTY(VisibleAnywhere, Category = "Location")
	int Y;

	UPROPERTY(VisibleAnywhere, Category = "Location")
	int X;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Components");
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditAnywhere, Category = "Sound")
	class USoundBase* ClickSound;

private:	
};
