// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));

	TankMovement = CreateDefaultSubobject<UTankMovementComponent>(FName("Movement Component"));
	if(!TankMovement)
		UE_LOG(LogTemp, Error, TEXT("DUPA"));
	
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
}

void ATank::AimAtLocation(const FVector & Target)
{
	TankAimingComponent->AimAtLocation(Target, LaunchSpeed);
}

void ATank::SetBarrelComponent(UTankBarrel * Component)
{
	TankAimingComponent->SetBarrelComponent(Component);
	Barrel = Component;
}


void ATank::SetTurretComponent(UTankTurret * Component)
{
	TankAimingComponent->SetTurretComponent(Component);
}

void ATank::Fire()
{
	if(!Barrel)
		return;

	if(FPlatformTime::Seconds() - LastTimeShot < ReloadTime)
		return;

	LastTimeShot = FPlatformTime::Seconds();
	Barrel->Shoot(ProjectileClass, LaunchSpeed);
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

