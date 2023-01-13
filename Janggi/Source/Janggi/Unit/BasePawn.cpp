#include "BasePawn.h"
#include "../Gun.h"
#include "../BlankSpawner.h"
#include "../JanggiGameStateBase.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h" 
#include "particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Misc/App.h"

ABasePawn::ABasePawn()
	:Team(0), HP(5.f), Damage(1.f), Move(1), UnitScore(100)
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	SetActorEnableCollision(false);
	CanBeDamaged();

	BaseScene = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Scene"));
	RootComponent = BaseScene;

	GunSpawnPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gun Spawn Point"));
	GunSpawnPoint->SetupAttachment(RootComponent);
		
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);
	BaseMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BaseMesh->OnClicked.AddDynamic(this, &ThisClass::UnitSelected);

	//SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	//SpringArm->SetupAttachment(RootComponent);

	//Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	//Camera->SetupAttachment(SpringArm);
}

void ABasePawn::BeginPlay()
{
	Super::BeginPlay();

	FoundMyTile();
}

void ABasePawn::FoundMyTile()
{
	auto GameState = Cast<AJanggiGameStateBase>(GetWorld()->GetGameState());

	for (int i = 0; i < GameState->BoardTiles.Num(); i++)
	{
		if (GameState->BoardTiles.IsValidIndex(i))
		{
			// 기물의 위치와 같은 타일 찾기
			auto Tile = Cast<ABlankTile>(GameState->BoardTiles[i]);
			if (Tile->GetTileInfo().Y == this->Y && 
				Tile->GetTileInfo().X == this->X)
			{
				CurrentTile = Tile;
			}
		}
	}
}

void ABasePawn::Attack(ABasePawn* TargetUnit)
{
	// TO DO
	// 1. 대상의 HP를 공격하는 유닛의 Damage만큼 뺌
	// 2. 총 생성
	// 3. 공격 모션
	// 4. 대상 Destroy

	if (TargetUnit)
	{
		int AttackedHP = TargetUnit->GetHP() - Damage;
		TargetUnit->SetHP(AttackedHP);
	}
	
	FVector Location = GunSpawnPoint->GetComponentLocation();
	FRotator Rotation = GunSpawnPoint->GetComponentRotation();

	auto Gun = GetWorld()->SpawnActor<AGun>(GunClass, Location, Rotation);

}

void ABasePawn::ServerAttack_Implementation(ABasePawn* TargetUnit)
{
	Attack(TargetUnit);
}

void ABasePawn::UnitSelected(UPrimitiveComponent* ClickedComp, FKey ButtonClicked)
{
	auto GameState = Cast<AJanggiGameStateBase>(GetWorld()->GetGameState());
	GameState->SetSelectedUnit(Cast<AActor>(this));
}

void ABasePawn::HandleDestruction()
{
	if (DeathParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(
			this,
			DeathParticle,
			GetActorLocation(),
			GetActorRotation()
		);
	}
}

void ABasePawn::SetCurrentTile(AActor* Tile)
{
	CurrentTile = Cast<ABlankTile>(Tile);
	Y = CurrentTile->GetTileInfo().Y;
	X = CurrentTile->GetTileInfo().X;
}

void ABasePawn::SetCurrentTileIsEmpty(int const Val)
{
	if (!ensure(CurrentTile != nullptr)) return;

	CurrentTile->SetTileIsEmpty(Val);
}

void ABasePawn::SetCurrentTileCurrentUnit(AActor* Unit)
{
	if (!ensure(CurrentTile != nullptr)) return;

	CurrentTile->SetCurrentUnit(Unit);

}

