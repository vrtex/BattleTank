// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Aiming Component"));

	TankAimingComponent->SetLaunchSpeed(LaunchSpeed);

}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = MaxHealth;
}

void ATank::AimAtLocation(const FVector & Target)
{
	TankAimingComponent->AimAtLocation(Target);
}

UTankAimingComponent * ATank::GetAimingComponent()
{
	return TankAimingComponent;
}

bool ATank::isLocked() const
{
	return TankAimingComponent->isLocked();
}

void ATank::Fire()
{
	TankAimingComponent->Fire();
}

float ATank::GetHealthPercent() const
{
	return CurrentHealth / MaxHealth;
}

float ATank::TakeDamage(float Damage, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	Super::TakeDamage(Damage, DamageEvent, EventInstigator, DamageCauser);
	CurrentHealth = FMath::Clamp<float>(CurrentHealth - Damage, 0, MaxHealth);
	if(CurrentHealth <= 0.01f)
		OnDeath.Broadcast();
	return Damage;
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
