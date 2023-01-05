// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuBase.h"
#include "InGame.generated.h"

/**
 * 
 */
UCLASS()
class JANGGI_API UInGame : public UMenuBase
{
	GENERATED_BODY()
	
public:
	UWorld* World;
	class AJanggiPlayerController* Controller;
	class AJanggiPlayerState* PlayerState;

protected:
	virtual bool Initialize() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* TimerText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Score;
};
