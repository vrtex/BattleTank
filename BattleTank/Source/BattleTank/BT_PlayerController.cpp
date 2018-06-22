// Fill out your copyright notice in the Description page of Project Settings.

#include "BT_PlayerController.h"



void ABT_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	if(GetControlledTank())
	{
		UE_LOG(LogTemp, Warning, TEXT("Controlling tank %s"), *GetControlledTank()->GetName());

	}
	else
		UE_LOG(LogTemp, Error, TEXT("No tank controlled"));


}

void ABT_PlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	AimTowardsCrosshair();
}

ATank * ABT_PlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

void ABT_PlayerController::AimTowardsCrosshair()
{
	ATank * Tank = GetControlledTank();
	if(!Tank) return;

	FVector HitLocation(0, 0, 0);
	UE_LOG(LogTemp, Warning, TEXT("Initial hit location: %s"), *HitLocation.ToString());

	if(!GetSightRayHitLocation(HitLocation))
		return;

	UE_LOG(LogTemp, Warning, TEXT("Hit location after line trace: %s"), *HitLocation.ToCompactString());

	// linetrace through the crosshair
	// get the impact point
	// point a barrel there
}

bool ABT_PlayerController::GetSightRayHitLocation(FVector & HitLocaton) const
{
	// Raycast from camera through crosshair
	// if it hits the ground or an enemy modify the HitLocation and returntrue
	// otherwise return false

	int32 SizeX, SizeY;

	GetViewportSize(SizeX, SizeY);
	
	FVector2D DotLocation(SizeX * CrosshairLocationX, SizeY * CrosshairLocationY);
	UE_LOG(LogTemp, Warning, TEXT("Dot location: %s"), *DotLocation.ToString());


	return false;
}