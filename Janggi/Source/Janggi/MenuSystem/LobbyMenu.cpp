// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyMenu.h"
#include "../JanggiGameInstance.h"
#include "../JanggiPlayerController.h"
#include "../JanggiGameStateBase.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Image.h"

bool ULobbyMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	World = GetWorld();
	if (!ensure(World != nullptr)) return false;

	Controller = Cast<AJanggiPlayerController>(World->GetFirstPlayerController());
	if (!ensure(Controller != nullptr)) return false;

	GameState = Cast<AJanggiGameStateBase>(World->GetGameState());
	if (!ensure(GameState != nullptr)) return false;

	GameInstance = Cast<UJanggiGameInstance>(World->GetGameInstance());
	if (!ensure(GameInstance != nullptr)) return false;

	if (!ensure(WaitWidget != nullptr)) return false;
	if (!ensure(ReadyMenu != nullptr)) return false;
	if (!ensure(CancelMenu != nullptr)) return false;
	if (!ensure(StartMenu != nullptr)) return false;
	if (!ensure(HostMenu != nullptr)) return false;
	if (!ensure(LobbyMenu != nullptr)) return false;
	if (!ensure(MenuSwitcher != nullptr)) return false;

	if (!ensure(BtnReady != nullptr)) return false;
	BtnReady->OnClicked.AddDynamic(this, &ThisClass::PressedOnBtnReady);

	if (!ensure(BtnCancel != nullptr)) return false;
	BtnCancel->OnClicked.AddDynamic(this, &ThisClass::PressedOnBtnCancel);

	if (!ensure(BtnStart != nullptr)) return false;
	BtnStart->OnClicked.AddDynamic(this, &ThisClass::PressedOnBtnStart);

	return true;
}

void ULobbyMenu::NativeConstruct()
{
	Super::NativeConstruct();
	UE_LOG(LogTemp, Warning, TEXT("NativeConstruct"));
}

void ULobbyMenu::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);



	if (Controller->HasAuthority())
	{	// Server
		if (!GameState->GetbClientReady())
		{
			MenuSwitcher->SetActiveWidget(HostMenu);
		}
		else
		{
			MenuSwitcher->SetActiveWidget(StartMenu);
		}
	}
	else
	{	// Client
		
	}
}

void ULobbyMenu::PressedOnBtnReady()
{
	Controller->ServerClientReady();

	WaitWidget->SetVisibility(ESlateVisibility::Visible);
	MenuSwitcher->SetActiveWidget(CancelMenu);
	BtnReady->SetIsEnabled(false);
	BtnCancel->SetIsEnabled(true);
}

void ULobbyMenu::PressedOnBtnCancel()
{
	Controller->ServerClientNotReady();

	WaitWidget->SetVisibility(ESlateVisibility::Hidden);
	MenuSwitcher->SetActiveWidget(ReadyMenu);
	BtnCancel->SetIsEnabled(false);
	BtnReady->SetIsEnabled(true);
}

void ULobbyMenu::PressedOnBtnStart()
{
	FString InGame = "/Game/Maps/InGame?listen";
	GameInstance->LoadLevel(InGame);
}

