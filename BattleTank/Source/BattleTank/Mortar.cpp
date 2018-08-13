// Fill out your copyright notice in the Description page of Project Settings.

#include "Mortar.h"


// Sets default values
AMortar::AMortar()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	AimComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("MortarAiming"));
}

// Called when the game starts or when spawned
void AMortar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMortar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMortar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMortar::AimAtLocation(const FVector & Location)
{
	if(!ensure(AimComponent))
		return;

	AimComponent->AimAtLocation(Location);
}

bool AMortar::isLocked() const
{
	if(!ensure(AimComponent))
		return false;
	return AimComponent->isLocked();
}

void AMortar::Fire()
{
	if(!ensure(AimComponent))
		return;

	AimComponent->Fire();
}
