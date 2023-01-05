// Fill out your copyright notice in the Description page of Project Settings.


#include "JanggiGameInstance.h"
#include "MenuSystem/MenuBase.h"
#include "MenuSystem/MainMenu.h"
#include "MenuSystem/LobbyMenu.h"
#include "MenuSystem/UserMenu.h"
#include "MenuSystem/InGame.h"

UJanggiGameInstance::UJanggiGameInstance(const FObjectInitializer& ObjectInitializer)
{
	UE_LOG(LogTemp, Warning, TEXT("Call GameInstance"));

	// MainMenu
	ConstructorHelpers::FClassFinder<UUserWidget>MainMenuBPClass(TEXT("/Game/MenuSystem/Blueprints/WBP_MainMenu"));
	if (MainMenuBPClass.Succeeded())
	{
		MainMenuClass = MainMenuBPClass.Class;
	}

	// LobbyMenu
	ConstructorHelpers::FClassFinder<UUserWidget>LobbyMenuBPClass(TEXT("/Game/MenuSystem/Blueprints/WBP_LobbyMenu"));
	if (LobbyMenuBPClass.Succeeded())
	{
		LobbyMenuClass = LobbyMenuBPClass.Class;
	}

	// InGameUI
	ConstructorHelpers::FClassFinder<UUserWidget>InGameUIBPClass(TEXT("/Game/MenuSystem/Blueprints/WBP_InGameUI"));
	if (InGameUIBPClass.Succeeded())
	{
		InGameUIClass = InGameUIBPClass.Class;
	}

	// UserMenu
	ConstructorHelpers::FClassFinder<UUserWidget>UserMenuBPClass(TEXT("/Game/MenuSystem/Blueprints/WBP_UserMenu"));
	if (UserMenuBPClass.Succeeded())
	{
		UserMenuClass = UserMenuBPClass.Class;
	}
}

void UJanggiGameInstance::LoadLevel(const FString& LevelAddress)
{
	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	if (PlayerController->HasAuthority())
	{
		UWorld* World = GetWorld();
		if (!ensure(World != nullptr)) return;
		World->ServerTravel(LevelAddress);
	}
	else
	{
		PlayerController->ClientTravel(LevelAddress, ETravelType::TRAVEL_Absolute);
	}
	
}

void UJanggiGameInstance::Host()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Hosting"));
	}

	UWorld* World = GetWorld();
	if (!ensure(World != nullptr)) return;
	World->ServerTravel("/Game/Maps/Lobby?listen");
}

void UJanggiGameInstance::Join(const FString& Address)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Joining %s"), *Address));
	}

	APlayerController* PlayerController = GetFirstLocalPlayerController();
	if (!ensure(PlayerController != nullptr)) return;

	PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}

void UJanggiGameInstance::LoadMainMenu()
{
	if (!ensure(MainMenuClass != nullptr)) return;
	MainMenu = CreateWidget<UMenuBase>(this, MainMenuClass);
	if (!ensure(MainMenu != nullptr)) return;

	MainMenu->SetUp_UIOnly();
	MainMenu->SetMenuInterface(this);
}

void UJanggiGameInstance::LoadLobbyMenu()
{
	if (!ensure(LobbyMenuClass != nullptr)) return;
	LobbyMenu = CreateWidget<UMenuBase>(this, LobbyMenuClass);
	if (!ensure(LobbyMenu != nullptr)) return;

	LobbyMenu->SetUp_UIOnly();
	LobbyMenu->SetMenuInterface(this);
}

void UJanggiGameInstance::LoadInGameUI()
{
	if (!ensure(InGameUIClass != nullptr)) return;
	InGameUI = CreateWidget<UMenuBase>(this, InGameUIClass);
	if (!ensure(InGameUI != nullptr)) return;

	InGameUI->SetUp_GameOnly();
	InGameUI->SetMenuInterface(this);
}

void UJanggiGameInstance::LoadUserMenu()
{
	if (!ensure(UserMenuClass != nullptr)) return;
	UserMenu = CreateWidget<UMenuBase>(this, UserMenuClass);
	if (!ensure(UserMenu != nullptr)) return;

	UserMenu->SetUp_UIOnly();
	UserMenu->SetMenuInterface(this);
}
