// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h" 
#include "particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"

ABasePawn::ABasePawn() : HP(0.f), Damage(0.f)
{
	PrimaryActorTick.bCanEverTick = true;
	SetActorEnableCollision(false);
	CanBeDamaged();

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	RootComponent = BaseMesh;
	BaseMesh->SetRelativeScale3D(FVector(3.0f, 3.0f, 3.0f));
	BaseMesh->OnClicked.AddDynamic(this, &ThisClass::UnitSelected);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SAMPLEMESH(TEXT("/Game/Food_Pack_01/Meshes/Food_Veg_Broccoli_01"));
	if (SAMPLEMESH.Succeeded())
	{
		BaseMesh->SetStaticMesh(SAMPLEMESH.Object);
	}

	//SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	//SpringArm->SetupAttachment(RootComponent);

	//Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	//Camera->SetupAttachment(SpringArm);
}

void ABasePawn::BeginPlay()
{
	Super::BeginPlay();

}

void ABasePawn::UnitSelected(UPrimitiveComponent* ClickedComp, FKey ButtonClicked)
{
	
}

void ABasePawn::HandleDestruction()
{
	
}

