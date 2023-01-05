// Fill out your copyright notice in the Description page of Project Settings.


#include "CameraDirector.h"
#include "Kismet/GameplayStatics.h"

ACameraDirector::ACameraDirector()
{
 	PrimaryActorTick.bCanEverTick = true;

}

void ACameraDirector::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACameraDirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	const float TimeBetweenCameraChanges = 2.f;
	const float SmoothBlendTime = 0.75f;

	TimeToNextCameraChage -= DeltaTime;
	if (TimeToNextCameraChage <= 0.f)
	{
		FChangeCameraData NowCamera = Cameras[NowCameraIndex];

		TimeToNextCameraChage += NowCamera.TimeBetweenCameraChanges;

		auto Controller = GetWorld()->GetFirstPlayerController();
		if (!ensure(Controller != nullptr)) return;

		if ((Controller->GetViewTarget() != NowCamera.Camera) && (NowCamera.Camera != nullptr))
		{
			if (NowCamera.SmoothBlendTime <= 0.f)
			{
				Controller->SetViewTarget(NowCamera.Camera);
			}
			else
			{
				Controller->SetViewTargetWithBlend(NowCamera.Camera, NowCamera.SmoothBlendTime);
			}
		}
	}
}

