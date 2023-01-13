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

	if (!ensure(WaitWidget != nullptr)) return false;
	if (!ensure(ReadyMenu != nullptr)) return false;
	if (!ensure(CancelMenu != nullptr)) return false;
	if (!ensure(StartMenu != nullptr)) return false;
	if (!ensure(HostMenu != nullptr)) return false;
	if (!ensure(LobbyMenu != nullptr)) return false;
	if (!ensure(TableSettingMenu != nullptr)) return false;
	if (!ensure(MenuSwitcher != nullptr)) return false;

	if (!ensure(BtnReady != nullptr)) return false;
	BtnReady->OnClicked.AddDynamic(this, &ThisClass::PressedOnBtnReady);

	if (!ensure(BtnCancel != nullptr)) return false;
	BtnCancel->OnClicked.AddDynamic(this, &ThisClass::PressedOnBtnCancel);

	if (!ensure(BtnStart != nullptr)) return false;
	BtnStart->OnClicked.AddDynamic(this, &ThisClass::PressedOnBtnStart);

	if (!ensure(BtnTable1 != nullptr)) return false;
	BtnTable1->OnClicked.AddDynamic(this, &ThisClass::PressedOnBtnTable1);

	if (!ensure(BtnTable2 != nullptr)) return false;
	BtnTable2->OnClicked.AddDynamic(this, &ThisClass::PressedOnBtnTable2);

	if (!ensure(BtnTable3 != nullptr)) return false;
	BtnTable3->OnClicked.AddDynamic(this, &ThisClass::PressedOnBtnTable3);

	if (!ensure(BtnTable4 != nullptr)) return false;
	BtnTable4->OnClicked.AddDynamic(this, &ThisClass::PressedOnBtnTable4);

	if (!ensure(BtnGo != nullptr)) return false;
	BtnGo->OnClicked.AddDynamic(this, &ThisClass::PressedOnBtnGo);
	BtnGo->SetIsEnabled(false);

	return true;
}

void ULobbyMenu::NativeConstruct()
{
	Super::NativeConstruct();

	World = GetWorld();
	if (!ensure(World != nullptr)) return;

	Controller = Cast<AJanggiPlayerController>(World->GetFirstPlayerController());
	if (!ensure(Controller != nullptr)) return;

	GameState = Cast<AJanggiGameStateBase>(World->GetGameState());
	if (!ensure(GameState != nullptr)) return;

	GameInstance = Cast<UJanggiGameInstance>(World->GetGameInstance());
	if (!ensure(GameInstance != nullptr)) return;
	
	GameInstance->TableType = 0;

	if (Controller->HasAuthority())
	{
		SetVisibleWaitWidget();
		MenuSwitcher->SetActiveWidget(HostMenu);	
	}
	else
	{
		SetHiddenWaitWidget();
		MenuSwitcher->SetActiveWidget(ReadyMenu);
	}
}

void ULobbyMenu::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);

	Controller->bShowMouseCursor = true;

	if (Controller->HasAuthority())
	{	// Server
		if (!GameState->GetbClientReady())
		{
			MenuSwitcher->SetActiveWidget(HostMenu);
		}
		else
		{
			if (BtnStart->GetIsEnabled() == true)
			{
				MenuSwitcher->SetActiveWidget(StartMenu);
			}
			else
			{
				MenuSwitcher->SetActiveWidget(TableSettingMenu);
			}
		}

		if (GameState->GetTableType() != 0)
		{
			BtnGo->SetIsEnabled(true);
		}
		else
		{
			BtnGo->SetIsEnabled(false);
		}
	}
	else
	{	// Client
		
	}
}

void ULobbyMenu::PressedOnBtnReady()
{
	if (!Controller->HasAuthority())
	{
		Controller->ServerClientReady();
		Controller->ServerSetHiddenWaitWidget();
		Controller->ServerSetEnabledTrueBtnStart();

		SetVisibleWaitWidget();
		MenuSwitcher->SetActiveWidget(CancelMenu);
		BtnReady->SetIsEnabled(false);
		BtnCancel->SetIsEnabled(true);
	}
}

void ULobbyMenu::PressedOnBtnCancel()
{
	if (!Controller->HasAuthority())
	{
		Controller->ServerSetTableType(0);
		Controller->ServerClientNotReady();
		Controller->ServerSetVisibleWaitWidget();
		Controller->ServerSetEnabledFalseBtnStart();

		SetHiddenWaitWidget();
		MenuSwitcher->SetActiveWidget(ReadyMenu);
		BtnCancel->SetIsEnabled(false);
		BtnReady->SetIsEnabled(true);
	}
}

void ULobbyMenu::PressedOnBtnStart()
{
	if (Controller->HasAuthority())
	{
		SetHiddenWaitWidget();
		BtnStart->SetIsEnabled(false);
	}
}

void ULobbyMenu::PressedOnBtnTable1()
{
	if (Controller->HasAuthority())
	{
		GameState->SetTableType(1);
	}
}

void ULobbyMenu::PressedOnBtnTable2()
{
	if (Controller->HasAuthority())
	{
		GameState->SetTableType(2);
	}
}

void ULobbyMenu::PressedOnBtnTable3()
{
	if (Controller->HasAuthority())
	{
		GameState->SetTableType(3);
	}
}

void ULobbyMenu::PressedOnBtnTable4()
{
	if (Controller->HasAuthority())
	{
		GameState->SetTableType(4);
	}
}

void ULobbyMenu::PressedOnBtnGo()
{
	FString InGame = "/Game/Maps/InGame?listen";
	GameInstance->LoadLevel(InGame);
}

void ULobbyMenu::SetVisibleWaitWidget()
{
	WaitWidget->SetVisibility(ESlateVisibility::Visible);
}

void ULobbyMenu::SetHiddenWaitWidget()
{
	WaitWidget->SetVisibility(ESlateVisibility::Hidden);
}

void ULobbyMenu::SetEnabledTrueBtnStart()
{
	BtnStart->SetIsEnabled(true);
}

void ULobbyMenu::SetEnabledFalseBtnStart()
{
	BtnStart->SetIsEnabled(false);
}

