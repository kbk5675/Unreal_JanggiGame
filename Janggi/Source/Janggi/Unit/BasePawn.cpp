#include "BasePawn.h"
#include "../Gun.h"
#include "../BlankSpawner.h"
#include "../JanggiGameStateBase.h"
#include "../JanggiPlayerController.h"
#include "../MovingPoint.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h" 
#include "particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"
#include "TimerManager.h"
#include "Misc/App.h"

ABasePawn::ABasePawn()
	:Team(0), HP(5.f), Damage(1.f), Move(1), UnitScore(100)
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	SetReplicateMovement(true);
		
	SetActorEnableCollision(false);
	CanBeDamaged();

	BaseScene = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Scene"));
	RootComponent = BaseScene;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(RootComponent);
	BaseMesh->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BaseMesh->OnClicked.AddDynamic(this, &ThisClass::UnitSelected);

	GunSpawnPoint = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Gun Spawn Point"));
	GunSpawnPoint->SetupAttachment(RootComponent);

	//SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	//SpringArm->SetupAttachment(RootComponent);
	//Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	//Camera->SetupAttachment(SpringArm);
}

void ABasePawn::BeginPlay()
{
	Super::BeginPlay();
}

void ABasePawn::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ThisClass, CurrentTile);
	DOREPLIFETIME(ThisClass, X);
	DOREPLIFETIME(ThisClass, Y);
}

void ABasePawn::UnitSelected(UPrimitiveComponent* ClickedComp, FKey ButtonClicked)
{
	auto GameState = Cast<AJanggiGameStateBase>(GetWorld()->GetGameState());

	if (this->HasAuthority())
	{
		if (this->Team == 1)
		{
			GameState->SetSelectedUnit(Cast<AActor>(this));
		}
	}
	else
	{
		if (this->Team == 2)
		{
			auto Con = Cast<AJanggiPlayerController>(GetWorld()->GetFirstPlayerController());
			Con->ServerSetSelectedUnit(Cast<AActor>(this));
		}
	}

	GEngine->AddOnScreenDebugMessage(-1, 1.5f, FColor::Purple, this->GetName());
}

void ABasePawn::Attack(ABasePawn* TargetUnit)
{
	auto Con = Cast<AJanggiPlayerController>(GetWorld()->GetFirstPlayerController());

	// 1. Reduce Target Unit's HP by Selected Unit's Damage
	if (TargetUnit)
	{
		int AttackedHP = TargetUnit->GetHP() - Damage;
		TargetUnit->SetHP(AttackedHP);
	}

	// 2. Run Dead if Target Unit's HP is below zero and Move Target Tile.
	if (TargetUnit->GetHP() <= 0)
	{
		auto TargetMovingPoint = Cast<AMovingPoint>(TargetUnit->CurrentTile->GetCurrentMovingPoint());
		if (TargetMovingPoint)
		{
			TargetMovingPoint->MoveUnit(this);
			
			if (HasAuthority())
			{
				TargetUnit->MulticastHandleDestruction();
			}
			else
			{
				Con->ServerBasePawnHandleDestruction(TargetUnit);	
			}
		}
	}
	
	// Spawn Gun
	/*if (HasAuthority())
	{
		FVector Location = GunSpawnPoint->GetComponentLocation();
		FRotator Rotation = GunSpawnPoint->GetComponentRotation();

		auto Gun = GetWorld()->SpawnActor<AGun>(GunClass, Location, Rotation);
		Gun->SetTargetLocation(TargetUnit->CurrentTile->GetCurrentMovingPoint()->GetActorLocation());
	}*/

}

void ABasePawn::HandleDestruction()
{
	if (DeathParticle)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, DeathParticle, GetActorLocation(), GetActorRotation());
	}

	if (DeathSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, DeathSound, GetActorLocation());
	}

	Destroy(true);
}

void ABasePawn::MulticastHandleDestruction_Implementation()
{
	HandleDestruction();
}

void ABasePawn::SetCurrentTile(AActor* Tile)
{
	CurrentTile = Cast<ABlankTile>(Tile);
}

void ABasePawn::SetCurrentTileAndPos(AActor* Tile)
{
	CurrentTile = Cast<ABlankTile>(Tile);
	Y = CurrentTile->GetTileInfo().Y;
	X = CurrentTile->GetTileInfo().X;
}

void ABasePawn::SetCurrentTileCurrentUnit(AActor* Unit)
{
	if (!ensure(CurrentTile != nullptr)) return;
	CurrentTile->SetCurrentUnit(Unit);
}