// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuBase.h"
#include "LobbyMenu.generated.h"

/**
 * 
 */
UCLASS()
class JANGGI_API ULobbyMenu : public UMenuBase
{
	GENERATED_BODY()
	
public:
	class UWorld* World;
	class UJanggiGameInstance* GameInstance;
	class AJanggiPlayerController* Controller;
	class AJanggiGameStateBase* GameState;
	
protected:
	virtual bool Initialize() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;

private:
	UFUNCTION()
	void PressedOnBtnReady();

	UFUNCTION()
	void PressedOnBtnCancel();

	UFUNCTION()
	void PressedOnBtnStart();

	UPROPERTY(meta = (BindWidget))
	class UButton* BtnReady;

	UPROPERTY(meta = (BindWidget))
	class UButton* BtnCancel;

	UPROPERTY(meta = (BindWidget))
	class UButton* BtnStart;

	UPROPERTY(meta = (BindWidget))
	class UWidgetSwitcher* MenuSwitcher;

	UPROPERTY(meta = (BindWidget))
	class UWidget* LobbyMenu;

	UPROPERTY(meta = (BindWidget))
	class UWidget* HostMenu;

	UPROPERTY(meta = (BindWidget))
	class UWidget* WaitWidget;

	UPROPERTY(meta = (BindWidget))
	class UWidget* ReadyMenu;

	UPROPERTY(meta = (BindWidget))
	class UWidget* CancelMenu;

	UPROPERTY(meta = (BindWidget))
	class UWidget* StartMenu;
};
