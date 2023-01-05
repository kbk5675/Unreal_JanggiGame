// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Unit/BasePawn.h"
#include "GameFramework/Actor.h"
#include "BlankTile.generated.h"

USTRUCT(BlueprintType)
struct FBlankTileInfo
{
	GENERATED_BODY()

	int X{};
	int Y{};
	int Z{};

	FBlankTileInfo() = default;
	FBlankTileInfo(int const NewX, int const NewY, int const NewZ)
		: X(NewX), Y(NewY), Z(NewZ)
	{

	}
};

UCLASS()
class JANGGI_API ABlankTile : public AActor
{
	GENERATED_BODY()
	
public:	
	ABlankTile();

	void SetTileInfo(FBlankTileInfo InTileInfo)
	{
		TileInfo = InTileInfo;
	}

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	class USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	class UStaticMeshComponent* BaseMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	class USceneComponent* UnitSpawnPoint;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Config", meta = (AllowPrivateAccess = true))
	FBlankTileInfo TileInfo;

	UPROPERTY(EditDefaultsOnly, Category = "Unit")
	TSubclassOf<class ABasePawn> UnitClass;

private:
	
};