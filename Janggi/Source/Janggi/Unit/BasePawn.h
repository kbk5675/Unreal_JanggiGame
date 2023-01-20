// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../BlankTile.h"
#include "GameFramework/Pawn.h"
#include "BasePawn.generated.h"

UCLASS()
class JANGGI_API ABasePawn : public APawn
{
	GENERATED_BODY()

//UFUNCTION
public:
	ABasePawn();

	void HandleDestruction();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastHandleDestruction();

	void SetCurrentTile(AActor* Tile);
	void SetCurrentTileAndPos(AActor* Tile);
	void SetCurrentTileCurrentUnit(AActor* Unit);

	void SetPosY(int Val)	{ Y = Val; }
	void SetPosX(int Val)	{ X = Val; }
	void SetHP(int Val)		{ HP = Val; }

	int GextPosY()	{ return Y; }
	int GextPosX()	{ return X; }
	int GetTeam()	{ return Team; }
	int GetHP()		{ return HP; }
	int GetDamage() { return Damage; }
	AActor* GetCurrentTile() { return Cast<AActor>(CurrentTile); }

	void Attack(ABasePawn* TargetUnit);

protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION()
	void UnitSelected(UPrimitiveComponent* ClickedComp, FKey ButtonClicked);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"));
	USceneComponent* BaseScene;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"));
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"));
	USceneComponent* GunSpawnPoint;

	/*UPROPERTY(EditInstanceOnly, Category = "Components")
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditInstanceOnly, Category = "Components")
	class UCameraComponent* Camera;*/

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	class UParticleSystem* DeathParticle;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* DeathSound;

	UPROPERTY(EditAnywhere, Category = "Combat")
	TSubclassOf<class AGun> GunClass;

	UPROPERTY(VisibleAnywhere, Replicated, Category = "Location")
	class ABlankTile* CurrentTile;

	UPROPERTY(VisibleAnywhere, Replicated, Category = "Location")
	int Y;

	UPROPERTY(VisibleAnywhere, Replicated, Category = "Location")
	int X;

	UPROPERTY(EditAnywhere, Category = "State")
	int Team;

	UPROPERTY(EditAnywhere, Category = "State")
	float HP;

	UPROPERTY(EditAnywhere, Category = "State")
	float Damage;

	UPROPERTY(EditAnywhere, Category = "State")
	int Move;

	UPROPERTY(EditAnywhere, Category = "State")
	int UnitScore;

private:
	FTimerHandle WaitHandle;
	float WaitTime = 2.5f;
};
