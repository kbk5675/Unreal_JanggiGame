// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MenuBase.h"
#include "UserMenu.generated.h"

/**
 * 
 */
UCLASS()
class JANGGI_API UUserMenu : public UMenuBase
{
	GENERATED_BODY()
	
public:

protected:
	virtual bool Initialize() override;

	UPROPERTY(meta = (BindWidget))
	class UButton* BtnCancel;

	UPROPERTY(meta = (BindWidget))
	class UButton* BtnQuit;

private:
	UFUNCTION()
	void BackToGame();

	UFUNCTION()
	void BackToMainMenu();
};
