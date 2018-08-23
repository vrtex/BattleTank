// Fill out your copyright notice in the Description page of Project Settings.

#include "BT_PlayerController.h"



void ABT_PlayerController::BeginPlay()
{
	Super::BeginPlay();

	if(ensure(GetControlledTank()))
	{
		UE_LOG(LogTemp, Warning, TEXT("Controlling tank %s"), *GetControlledTank()->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No tank controlled"));
	}

	if(GetControlledTank())
		FoundAimingComponent(GetControlledTank()->GetAimingComponent());
}

void ABT_PlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if(!GetControlledTank())
		return;
	AimTowardsCrosshair();
}

void ABT_PlayerController::SetPawn(APawn * NewPawn)
{
	Super::SetPawn(NewPawn);

	if(!NewPawn)
		return;

	ATank * PossesedTank = Cast<ATank>(NewPawn);
	if(!PossesedTank)
		return;

	PossesedTank->OnDeath.AddUniqueDynamic(this, &ABT_PlayerController::OnTankDeath);
}

ATank * ABT_PlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


void ABT_PlayerController::OnTankDeath()
{
	/*
	GetControlledTank()->DetachFromControllerPendingDestroy();
	*/
	StartSpectatingOnly();
	
}
void ABT_PlayerController::AimTowardsCrosshair()
{
	ATank * Tank = GetControlledTank();
	if(!ensure(Tank)) return;

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
	bool bLookingAtGround = GetWorld()->LineTraceSingleByChannel(HitResult, TankLocation, TraceEnd, ECollisionChannel::ECC_Camera);
	if(!bLookingAtGround) return false;
	HitLocaton = HitResult.Location;
	return true;
}

void ABT_PlayerController::GetWorldDirection(FVector2D ScreenLocation, FVector & WorldDirection) const
{
	FVector CameraLocation;
	DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraLocation, WorldDirection);
}
