// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));
}

void ATank::AimAtLocation(const FVector & Target)
{
	TankAimingComponent->AimAtLocation(Target, LaunchSpeed);
}

void ATank::SetBarrelComponent(UTankBarrel * Component)
{
	TankAimingComponent->SetBarrelComponent(Component);
}


void ATank::SetTurretComponent(UStaticMeshComponent * Component)
{
	TankAimingComponent->SetTurretComponent(Component);
}


// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

