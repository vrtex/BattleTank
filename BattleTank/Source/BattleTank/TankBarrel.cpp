// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.f, 1.f);
	float ElevationChange = RelativeSpeed * MaxSpeed * GetWorld()->DeltaTimeSeconds;
	float NewElevation = RelativeRotation.Pitch + ElevationChange;
	NewElevation = FMath::Clamp(NewElevation, MinElevation, MaxElevation);

	SetRelativeRotation(FRotator(NewElevation, 0, 0));
}

void UTankBarrel::Shoot(TSubclassOf<AProjectile> ProjectileClass, float Speed) const
{
	if(!ensure(ProjectileClass))
	{
		UE_LOG(LogTemp, Error, TEXT("Stupid projjectile class"));
		FGenericPlatformMisc::RequestExit(false);
		return;
	}
	FVector Location = GetSocketLocation(FName("FiringPoint"));
	FRotator Rotation = GetSocketRotation(FName("FiringPoint"));

	AProjectile * Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Location, Rotation);

	UE_LOG(LogTemp, Warning, TEXT("Fire"));

	Projectile->Launch(Speed);
}