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

	UFUNCTION()
	void OnClickedMovingPoint(UPrimitiveComponent* ClickedComp, FKey ButtonClicked);

	void MoveUnit(AActor* Unit);
	void MoveSelectedUnit(AActor* Unit);
	void HandleDestruction();

	UPROPERTY(VisibleAnywhere, Replicated, Category = "Location")
	class ABlankTile* CurrentTile;

	UPROPERTY(VisibleAnywhere, Replicated, Category = "Location")
	int Y;

	UPROPERTY(VisibleAnywhere, Replicated, Category = "Location")
	int X;

protected:
	virtual void BeginPlay() override;
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Components");
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditAnywhere, Category = "Sound")
	class USoundBase* ClickSound;

private:	
};
