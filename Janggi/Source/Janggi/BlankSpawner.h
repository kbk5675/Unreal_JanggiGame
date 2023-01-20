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
	void BuildBoard(const FVector CenteredLocation, const int X, const int Y, const TArray<int> TableType);

public:	
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	FVector2D BoardSize;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<class ABlankTile*> BoardTiles;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float SectorSize;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftClassPtr<ABlankTile> TileClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftClassPtr<ABlankTile> ChaBlueTileClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftClassPtr<ABlankTile> JoleBlueTileClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftClassPtr<ABlankTile> KingBlueTileClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftClassPtr<ABlankTile> MaBlueTileClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftClassPtr<ABlankTile> PhoBlueTileClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftClassPtr<ABlankTile> SaBlueTileClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftClassPtr<ABlankTile> SangBlueTileClass;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftClassPtr<ABlankTile> ChaRedTileClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftClassPtr<ABlankTile> JoleRedTileClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftClassPtr<ABlankTile> KingRedTileClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftClassPtr<ABlankTile> MaRedTileClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftClassPtr<ABlankTile> PhoRedTileClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftClassPtr<ABlankTile> SaRedTileClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSoftClassPtr<ABlankTile> SangRedTileClass;

private:
	TArray<int>TableType1 = { 0,1,0,6,9,1,9,6,0,2,0,7,9,2,9,7 };
	TArray<int>TableType2 = { 0,2,0,7,9,2,9,7,0,1,0,6,9,1,9,6 };
	TArray<int>TableType3 = { 0,1,0,7,9,1,9,7,0,2,0,6,9,2,9,6 };
	TArray<int>TableType4 = { 0,2,0,6,9,2,9,6,0,1,0,7,9,1,9,7 };
};
