// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPoint.h"
#include "Unit/BasePawn.h"
#include "BlankTile.h"
#include "JanggiGameStateBase.h"
#include "JanggiPlayerController.h"
#include "Sound/SoundBase.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

AMovingPoint::AMovingPoint()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->OnClicked.AddDynamic(this, &ThisClass::OnClickedMovingPoint);
	RootComponent = BaseMesh;
	BaseMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	ClickSound = CreateDefaultSubobject<USoundBase>(TEXT("Click Sound"));
}

void AMovingPoint::BeginPlay()
{
	Super::BeginPlay();

	
}

void AMovingPoint::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, CurrentTile);
	DOREPLIFETIME(ThisClass, Y);
	DOREPLIFETIME(ThisClass, X);
}

void AMovingPoint::OnClickedMovingPoint(UPrimitiveComponent* ClickedComp, FKey ButtonClicked)
{
	auto GameState = Cast<AJanggiGameStateBase>(GetWorld()->GetGameState());
	if (GameState)
	{
		AActor* SelectedUnit = GameState->GetSelectedUnit();
		if (SelectedUnit)
		{
			if (Cast<ABasePawn>(this->CurrentTile->GetCurrentUnit()))
			{
				// Attack Trigger
				if (Cast<ABasePawn>(SelectedUnit)->GetTeam() != Cast<ABasePawn>(this->CurrentTile->GetCurrentUnit())->GetTeam())
				{
					Cast<ABasePawn>(SelectedUnit)->Attack(Cast<ABasePawn>(this->CurrentTile->GetCurrentUnit()));
					HandleDestruction();
				}
			}
			else
			{
				MoveUnit(SelectedUnit);
			}
		}
		else
		{
			UE_LOG(LogTemp, Error, TEXT("Can't Found Selected Unit!"));
		}
	}
}

void AMovingPoint::MoveUnit(AActor* Unit)
{
	auto JanggiUnit = Cast<ABasePawn>(Unit);
	if (JanggiUnit)
	{
		if (HasAuthority())
		{
			JanggiUnit->SetCurrentTileCurrentUnit(nullptr);		// 이동 하기 전 타일의 '현재 유닛' 변수 NULL로 변경
			this->CurrentTile->SetCurrentUnit(JanggiUnit);		// 이동한       타일의 '현재 유닛'을 선택유닛으로 변경

			MoveSelectedUnit(JanggiUnit);						// 이동

			JanggiUnit->SetCurrentTile(this->CurrentTile);		// 선택유닛의 '현재 타일' 변경
			JanggiUnit->SetPosY(this->Y);						// 선택유닛의 'X Y 좌표'  변경
			JanggiUnit->SetPosX(this->X);
		}
		else
		{
			auto Controller = Cast<AJanggiPlayerController>(GetWorld()->GetFirstPlayerController());
			if (Controller)
			{
				Controller->ServerSetCurrentTileCurrentUnit(JanggiUnit, nullptr);
				Controller->ServerSetCurrentUnit(this->CurrentTile, JanggiUnit);

				Controller->ServerMoveSelectedUnit(this, JanggiUnit);

				Controller->ServerSetCurrentTile(JanggiUnit, this->CurrentTile);
				Controller->ServerSetPosY(JanggiUnit, Y);
				Controller->ServerSetPosX(JanggiUnit, X);	
			}
		}

		HandleDestruction();
	}
}

void AMovingPoint::HandleDestruction()
{
	if (ClickSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ClickSound, GetActorLocation());
	}

	auto GameState = Cast<AJanggiGameStateBase>(GetWorld()->GetGameState());
	auto MovingPoints = GameState->MovingPoints;

	for (int i = 0; i < MovingPoints.Num(); i++)
	{
		auto MovingPoint = Cast<AMovingPoint>(MovingPoints[i]);
		if (MovingPoint)
		{
			if (HasAuthority())
			{
				MovingPoint->SetActorHiddenInGame(true);
			}
			else
			{
				auto Controller = Cast<AJanggiPlayerController>(GetWorld()->GetFirstPlayerController());
				Controller->ServerSetVisibleMovingPoint(MovingPoint, true);
			}
			
		}
	}
}

void AMovingPoint::MoveSelectedUnit(AActor* Unit)
{
	Unit->SetActorLocation(this->GetTargetLocation());
}


