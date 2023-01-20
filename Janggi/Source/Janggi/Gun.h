// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class JANGGI_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	AGun();
	
	void SetTargetLocation(FVector Location);

	FTimerHandle DestroyTimer;

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"));
	USceneComponent* BaseScene;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"));
	USkeletalMeshComponent* GunMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"));
	USceneComponent* ProjectileSpawnPoint;

	void HandleDestruction();

private:	
	UPROPERTY(VisibleAnywhere)
	FVector TargetLocation;

	UPROPERTY(VisibleAnywhere)
	FVector GlobalTargetLocation;

	UPROPERTY(VisibleAnywhere)
	FVector GlobalStartLocation;

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = "true"));
	float Speed = 0.f;

	

	UPROPERTY(EditAnywhere)
	int Time = 2.f;
};