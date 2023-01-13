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

	UPROPERTY(EditAnywhere, Category = "TileInfo")
	int X{};
	UPROPERTY(EditAnywhere, Category = "TileInfo")
	int Y{};
	UPROPERTY(EditAnywhere, Category = "TileInfo")
	int Z{};
	UPROPERTY(EditAnywhere, Category = "TileInfo")
	int TileIsEmpty{};

	FBlankTileInfo() = default;
	FBlankTileInfo(int const NewX, int const NewY, int const NewZ) : X(NewX), Y(NewY), Z(NewZ), TileIsEmpty(0) {}
};

UCLASS()
class JANGGI_API ABlankTile : public AActor
{
	GENERATED_BODY()
	
public:	
	ABlankTile();

	void SetTileInfo(FBlankTileInfo InTileInfo) { TileInfo = InTileInfo; }
	FBlankTileInfo GetTileInfo() { return TileInfo; }

	void SetTileIsEmpty(int const Val) { TileInfo.TileIsEmpty = Val; }

	void SetCurrentUnit(AActor* Unit);
	AActor* GetCurrentUnit() { return Cast<AActor>(CurrentUnit); }

	void SpawnUnit();
	void SpawnMovePoint(int const MovingUnitTeamInfo);

	void SetbIsSpawnMovingPoint(bool const bVal) { bIsSpawnMovingPoint = bVal; }
	bool GetbIsSpawnMovingPoint() { return bIsSpawnMovingPoint; }

	FVector GetSlotLocation() { return UnitSlot->GetComponentLocation(); }

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	class USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	class UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	class USceneComponent* UnitSlot;

	UPROPERTY(VisibleAnywhere, Category = "Config", meta = (AllowPrivateAccess = true))
	FBlankTileInfo TileInfo;

	UPROPERTY(EditDefaultsOnly, Category = "Config")
	TSubclassOf<class ABasePawn> SpawnUnitClass;

	UPROPERTY(EditDefaultsOnly, Category = "Config")
	TSubclassOf<class AActor> MovingPointClass;

	UPROPERTY(VisibleAnywhere, Category = "Unit")
	class ABasePawn* CurrentUnit;

	UPROPERTY(VisibleAnywhere, Category = "Config")
	bool bIsSpawnMovingPoint;

private:
	
};
