// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CameraDirector.generated.h"

USTRUCT(Atomic, BlueprintType)
struct FChangeCameraData
{
	GENERATED_BODY();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float TimeBetweenCameraChanges;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SmoothBlendTime;
};

UCLASS()
class JANGGI_API ACameraDirector : public AActor
{
	GENERATED_BODY()
	
public:	
	ACameraDirector();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere, Category = Camera, meta = (AllowPrivateAccess))
		TArray<FChangeCameraData> Cameras;

	int32 NowCameraIndex;

	UPROPERTY(EditAnywhere, Category = Camera, meta = (AllowPrivateAccess))
	float TimeToNextCameraChage;

};
