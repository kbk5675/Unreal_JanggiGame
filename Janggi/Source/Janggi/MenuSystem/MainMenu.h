// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuBase.h"
#include "MainMenu.generated.h"

/**
 * 
 */
UCLASS()
class JANGGI_API UMainMenu : public UMenuBase
{
	GENERATED_BODY()
	
protected:
	virtual bool Initialize() override;

protected:
	UFUNCTION()
		void HostServer();

	UFUNCTION()
		void JoinServer();

	UFUNCTION()
		void ExitGame();

	UFUNCTION()
		void OpenJoinMenu();

	UFUNCTION()
		void OpenMainMenu();

private:
	UPROPERTY(meta = (BindWidget))
		class UButton* BtnHost;

	UPROPERTY(meta = (BindWidget))
		class UButton* BtnJoin;

	UPROPERTY(meta = (BindWidget))
		class UButton* BtnExit;

	UPROPERTY(meta = (BindWidget))
		class UButton* BtnConfirmJoin;

	UPROPERTY(meta = (BindWidget))
		class UButton* BtnCancel;

	UPROPERTY(meta = (BindWidget))
		class UEditableTextBox* IPAddressField;

	UPROPERTY(meta = (BindWidget))
		class UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
		class UWidget* JoinMenu;

	UPROPERTY(meta = (BindWidget))
		class UWidget* MainMenu;

};
