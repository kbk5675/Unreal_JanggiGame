// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"

bool UMainMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(IPAddressField != nullptr)) return false;
	if (!ensure(MenuSwitcher != nullptr)) return false;

	if (!ensure(BtnHost != nullptr)) return false;
	BtnHost->OnClicked.AddDynamic(this, &ThisClass::HostServer);

	if (!ensure(BtnJoin != nullptr)) return false;
	BtnJoin->OnClicked.AddDynamic(this, &ThisClass::OpenJoinMenu);

	if (!ensure(BtnExit != nullptr)) return false;
	BtnExit->OnClicked.AddDynamic(this, &ThisClass::ExitGame);

	if (!ensure(BtnConfirmJoin != nullptr)) return false;
	BtnConfirmJoin->OnClicked.AddDynamic(this, &ThisClass::JoinServer);

	if (!ensure(BtnCancel != nullptr)) return false;
	BtnCancel->OnClicked.AddDynamic(this, &ThisClass::OpenMainMenu);

	return true;
}

void UMainMenu::HostServer()
{
	if (MenuInterface != nullptr)
	{
		MenuInterface->Host();
	}
}

void UMainMenu::JoinServer()
{
	if (MenuInterface != nullptr)
	{
		const FString& Address = IPAddressField->GetText().ToString();
		MenuInterface->Join(Address);
	}
}

void UMainMenu::OpenJoinMenu()
{
	MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UMainMenu::OpenMainMenu()
{
	MenuSwitcher->SetActiveWidget(MainMenu);
}

void UMainMenu::ExitGame()
{
	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;

	APlayerController* PlayerController = World->GetFirstPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ConsoleCommand("quit");
}
