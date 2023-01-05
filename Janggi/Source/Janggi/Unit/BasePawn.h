// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
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

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void UnitSelected(UPrimitiveComponent* ClickedComp, FKey ButtonClicked);

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"));
	UStaticMeshComponent* BaseMesh;

	/*UPROPERTY(EditInstanceOnly, Category = "Components")
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditInstanceOnly, Category = "Components")
	class UCameraComponent* Camera;*/

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	class UParticleSystem* DeathParticle;

	UPROPERTY(EditAnywhere, Category = "Combat")
	class USoundBase* DeathSound;

	UPROPERTY(EditAnywhere, Category = "States")
	float HP;

	UPROPERTY(EditAnywhere, Category = "States")
	float Damage;

	UPROPERTY(EditAnywhere, Category = "States")
	int UnitScore;

private:
	
};
