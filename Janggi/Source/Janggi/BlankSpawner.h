// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BlankTile.h"
#include "GameFramework/Actor.h"
#include "BlankSpawner.generated.h"

UCLASS()
class JANGGI_API ABlankSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	ABlankSpawner();

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void BuildBoard(const FVector CenteredLocation, const int X, const int Y);

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector2D BoardSize;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<class AActor*> BoardTiles;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TSoftClassPtr<ABlankTile> TileClass;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TSoftClassPtr<ABlankTile> ChaTileClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TSoftClassPtr<ABlankTile> JoleTileClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TSoftClassPtr<ABlankTile> KingTileClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TSoftClassPtr<ABlankTile> MaTileClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TSoftClassPtr<ABlankTile> PhoTileClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TSoftClassPtr<ABlankTile> SaTileClass;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TSoftClassPtr<ABlankTile> SangTileClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SectorSize;
};
