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
	{
		UE_LOG(LogTemp, Error, TEXT("No tank controlled"));
	}

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

	if(GetSightRayHitLocation(HitLocation))
	{
		Tank->AimAtLocation(HitLocation);
	}
	return;
}

bool ABT_PlayerController::GetSightRayHitLocation(FVector & HitLocaton) const
{
	// Raycast from camera through crosshair
	// if it hits the ground or an enemy modify the HitLocation and returntrue
	// otherwise return false

	int32 SizeX, SizeY;
	FVector LookDirection;

	GetViewportSize(SizeX, SizeY);
	
	FVector2D DotLocation(SizeX * CrosshairLocationX, SizeY * CrosshairLocationY);
	GetWorldDirection(DotLocation, LookDirection);

	FHitResult HitResult;
	FVector TankLocation = PlayerCameraManager->GetCameraLocation();
	FVector TraceEnd = TankLocation + LookDirection * AimRange;
	bool bLookingAtGround = GetWorld()->LineTraceSingleByChannel(HitResult, TankLocation, TraceEnd, ECollisionChannel::ECC_Visibility);
	if(!bLookingAtGround) return false;
	HitLocaton = HitResult.Location;
	return true;
}

void ABT_PlayerController::GetWorldDirection(FVector2D ScreenLocation, FVector & WorldDirection) const
{
	FVector CameraLocation;
	DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraLocation, WorldDirection);
}
