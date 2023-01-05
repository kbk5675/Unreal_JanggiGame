// Fill out your copyright notice in the Description page of Project Settings.


#include "UserMenu.h"
#include "Components/Button.h"

bool UUserMenu::Initialize()
{
	bool Success = Super::Initialize();
	if (!Success) return false;

	if (!ensure(BtnCancel != nullptr)) return false;
	BtnCancel->OnClicked.AddDynamic(this, &ThisClass::BackToGame);

	if (!ensure(BtnQuit != nullptr)) return false;
	BtnQuit->OnClicked.AddDynamic(this, &ThisClass::BackToMainMenu);

	return true;
}

void UUserMenu::BackToGame()
{
	OnLevelRemovedFromWorld(GetWorld()->GetLevel(0), GetWorld());
}

void UUserMenu::BackToMainMenu()
{
	if (MenuInterface != nullptr)
	{
		OnLevelRemovedFromWorld(GetWorld()->GetLevel(0), GetWorld());
		
		FString MainMenuLevelAddress= "/Game/Maps/Lobby?listen";
		MenuInterface->LoadLevel(MainMenuLevelAddress);
	}
}