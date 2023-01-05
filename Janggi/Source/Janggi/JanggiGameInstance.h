// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MenuSystem/MenuInterface.h"
#include "JanggiGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class JANGGI_API UJanggiGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()

public:
	UJanggiGameInstance(const FObjectInitializer& ObjectInitializer);

	virtual void LoadLevel(const FString& LevelAddress) override;

	UFUNCTION(Exec)
	void Host();

	UFUNCTION(Exec)
	void Join(const FString& Address);

	UFUNCTION(Exec, BlueprintCallable)
	void LoadMainMenu();

	UFUNCTION(Exec, BlueprintCallable)
	void LoadLobbyMenu();

	UFUNCTION(Exec, BlueprintCallable)
	void LoadInGameUI();

	UFUNCTION(Exec, BlueprintCallable)
	void LoadUserMenu();

	
	UPROPERTY()
	TSubclassOf<class UUserWidget> MainMenuClass;

	UPROPERTY()
	TSubclassOf<class UUserWidget> LobbyMenuClass;

	UPROPERTY()
	TSubclassOf<class UUserWidget> InGameUIClass;

	UPROPERTY()
	TSubclassOf<class UUserWidget> UserMenuClass;


	class UMenuBase* MainMenu;
	class UMenuBase* LobbyMenu;
	class UMenuBase* UserMenu;
	class UMenuBase* InGameUI;
};