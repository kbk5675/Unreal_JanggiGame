// Fill out your copyright notice in the Description page of Project Settings.


#include "Jole.h"
#include "../JanggiGameStateBase.h"
#include "../JanggiPlayerController.h"
#include "../BlankTile.h"

AJole::AJole()
{
	HP = 100;
	Damage = 20;
	Move = 1;
	UnitScore = 2;

	BaseMesh->OnClicked.AddDynamic(this, &ThisClass::OnClickJole);
}

void AJole::BeginPlay()
{
	Super::BeginPlay();

}

void AJole::OnClickJole(UPrimitiveComponent* ClickedComp, FKey ButtonClicked)
{
	auto PlayerController = Cast<AJanggiPlayerController>(GetWorld()->GetFirstPlayerController());
	auto GameState = Cast<AJanggiGameStateBase>(GetWorld()->GetGameState());

	if (HasAuthority())
	{
		if (Team == 1)
		{
			GameState->FindMoveableTile(Y + 1, X);
			GameState->FindMoveableTile(Y, X - 1);
			GameState->FindMoveableTile(Y, X + 1);
		}
	}
	else
	{
		if (Team == 2)
		{
			GameState->FindMoveableTile(Y - 1, X);
			GameState->FindMoveableTile(Y, X - 1);
			GameState->FindMoveableTile(Y, X + 1);
		}
	}
}



