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
	
	if (!ensure(TimerText != nullptr)) return false;

	return true;
}

void UInGame::NativeConstruct()
{
	Super::NativeConstruct();

	World = GetWorld();
	if (!ensure(World != nullptr)) return;

	GameInstance = Cast<UJanggiGameInstance>(World->GetGameInstance());
	if (!ensure(GameInstance != nullptr)) return;

	Controller = Cast<AJanggiPlayerController>(World->GetFirstPlayerController());
	if (!ensure(Controller != nullptr)) return;

	GameState = Cast<AJanggiGameStateBase>(World->GetGameState());
	if (!ensure(GameState != nullptr)) return;
}

void UInGame::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);

	Controller->bShowMouseCursor = true;

	PlayerState = Cast<AJanggiPlayerState>(Controller->PlayerState);
	if (PlayerState)
	{
		Score->SetText(FText::FromString(FString::FromInt(PlayerState->GetPlayerScore())));
	}

	auto SelectedUnit = Cast<ABasePawn>(GameState->GetSelectedUnit());
	/*if(SelectedUnit) GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, FString::Printf(TEXT("X : %d   Y: %d")
		, SelectedUnit->GextPosX(), SelectedUnit->GextPosY()));*/
}