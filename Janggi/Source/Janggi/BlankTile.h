// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Unit/BasePawn.h"
#include "MovingPoint.h"
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
	
	FBlankTileInfo() = default;
	FBlankTileInfo(int const NewX, int const NewY, int const NewZ) : X(NewX), Y(NewY), Z(NewZ) {}
};

UCLASS()
class JANGGI_API ABlankTile : public AActor
{
	GENERATED_BODY()
	
public:	
	ABlankTile();

	void SetTileInfo(FBlankTileInfo InTileInfo)		{ TileInfo = InTileInfo; }
	void SetCurrentMovingPoint(AActor* MovingPoint) { CurrentMovingPoint = Cast<AMovingPoint>(MovingPoint); }
	void SetCurrentUnit(AActor* Unit);
	
	FBlankTileInfo	GetTileInfo()			{ return TileInfo; }
	FVector			GetSlotLocation()		{ return UnitSlot->GetComponentLocation(); }
	AActor*			GetCurrentUnit()		{ return Cast<AActor>(CurrentUnit); }
	AActor*			GetCurrentMovingPoint() { return Cast<AActor>(CurrentMovingPoint); }


protected:
	virtual void BeginPlay() override;
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	void SpawnActors();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	class USceneComponent* SceneComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	class UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
	class USceneComponent* UnitSlot;

	UPROPERTY(EditDefaultsOnly, Category = "Config")
	TSubclassOf<class ABasePawn> SpawnUnitClass;

	UPROPERTY(EditDefaultsOnly, Category = "Config")
	TSubclassOf<class AActor> MovingPointClass;

	UPROPERTY(VisibleAnywhere, Replicated, Category = "Config", meta = (AllowPrivateAccess = true))
	FBlankTileInfo TileInfo;

	UPROPERTY(VisibleAnywhere, Replicated, Category = "Unit")
	class ABasePawn* CurrentUnit;

	UPROPERTY(VisibleAnywhere, Replicated, Category = "Unit")
	class AMovingPoint* CurrentMovingPoint;

private:
	
};
