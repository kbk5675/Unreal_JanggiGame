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

	void SetCurrentTile(AActor* Tile);
	void SetCurrentTileIsEmpty(int const Val);
	void SetCurrentTileCurrentUnit(AActor* Unit);
	void SetPosY(int Val) { Y = Val; }
	void SetPosX(int Val) { X = Val; }

	int GextPosY() { return Y; }
	int GextPosX() { return X; }

	int GetTeam() { return Team; }

	void SetHP(int const Val) { HP = Val; }
	int GetHP() { return HP; }

	void SetDamage(int const Val) { HP = Damage; }
	int GetDamage() { return Damage; }

	void FoundMyTile();
	
	void Attack(ABasePawn* TargetUnit);

	UFUNCTION(Server, Reliable)
	void ServerAttack(ABasePawn* TargetUnit);
	void ServerAttack_Implementation(ABasePawn* TargetUnit);


protected:
	virtual void BeginPlay() override;

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

	UPROPERTY(VisibleAnywhere, Category = "Location")
	class ABlankTile* CurrentTile;

	UPROPERTY(VisibleAnywhere, Category = "Location")
	int Y;

	UPROPERTY(VisibleAnywhere, Category = "Location")
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

	UPROPERTY(EditAnywhere, Category = "Config")
	TSubclassOf<class AGun> GunClass;

private:
	
};
