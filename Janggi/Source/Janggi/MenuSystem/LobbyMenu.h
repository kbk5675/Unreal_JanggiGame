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

	void SetVisibleWaitWidget();
	void SetHiddenWaitWidget();

	void SetEnabledTrueBtnStart();
	void SetEnabledFalseBtnStart();

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

	UFUNCTION()
	void PressedOnBtnTable1();

	UFUNCTION()
	void PressedOnBtnTable2();

	UFUNCTION()
	void PressedOnBtnTable3();

	UFUNCTION()
	void PressedOnBtnTable4();

	UFUNCTION()
	void PressedOnBtnGo();


	UPROPERTY(meta = (BindWidget))
	class UButton* BtnReady;

	UPROPERTY(meta = (BindWidget))
	class UButton* BtnCancel;

	UPROPERTY(meta = (BindWidget))
	class UButton* BtnStart;

	UPROPERTY(meta = (BindWidget))
	class UButton* BtnTable1;

	UPROPERTY(meta = (BindWidget))
	class UButton* BtnTable2;

	UPROPERTY(meta = (BindWidget))
	class UButton* BtnTable3;

	UPROPERTY(meta = (BindWidget))
	class UButton* BtnTable4;

	UPROPERTY(meta = (BindWidget))
	class UButton* BtnGo;

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

	UPROPERTY(meta = (BindWidget))
	class UWidget* TableSettingMenu;
};
