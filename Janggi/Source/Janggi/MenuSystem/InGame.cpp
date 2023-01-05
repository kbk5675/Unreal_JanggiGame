// Fill out your copyright notice in the Description page of Project Settings.


#include "InGame.h"
#include "../JanggiGameInstance.h"
#include "../JanggiPlayerController.h"
#include "../JanggiGameStateBase.h"
#include "../JanggiPlayerState.h"
#include "Components/TextBlock.h"

bool UInGame::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	UE_LOG(LogTemp, Warning, TEXT("Initialize"));

	if (!ensure(TimerText != nullptr)) return false;

	World = GetWorld();
	if (!ensure(World != nullptr)) return false;

	Controller = Cast<AJanggiPlayerController>(World->GetFirstPlayerController());
	if (!ensure(Controller != nullptr)) return false;
	
	PlayerState = Cast<AJanggiPlayerState>(Controller->PlayerState);
	if (!ensure(PlayerState != nullptr)) return false;

	return true;
}

void UInGame::NativeConstruct()
{
	Super::NativeConstruct();

}

void UInGame::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);


	Score->SetText(FText::FromString(FString::FromInt(PlayerState->GetPlayerScore())));

}