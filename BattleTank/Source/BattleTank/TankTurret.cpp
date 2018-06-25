// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"


void UTankTurret::Rotate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.f, 1.f);
	float CurrentYaw = RelativeRotation.Yaw;
	float Delta = RelativeSpeed * GetWorld()->DeltaTimeSeconds * RotateSpeed;
	
	float NewYaw = CurrentYaw + Delta;
	SetRelativeRotation(FRotator(0, NewYaw, 0));
}
