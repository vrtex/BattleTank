// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TankMovementComponent.h"
#include "TankTrack.h"
#include "Projectile.h"
#include "TankTurret.h"
#include "TankBarrel.h"
#include "TankAimingComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	void AimAtLocation(const FVector & Target);

	UFUNCTION(Blueprintcallable, Category = Setup)
		void SetBarrelComponent(UTankBarrel * Component);

	UFUNCTION(Blueprintcallable, Category = Setup)
		void SetTurretComponent(UTankTurret * Component);

	/*
	UFUNCTION(Blueprintcallable, Category = Setup)
		void SetTracks(UTankTrack * Left, UTankTrack * Right);
	*/

	UFUNCTION(Blueprintcallable)
		void Fire();

	
	UPROPERTY(EditDefaultsOnly, Category = Firing)
		float LaunchSpeed = 8000.f;


	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AProjectile> ProjectileClass;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UTankAimingComponent * TankAimingComponent = nullptr;

public:

	/*
	UPROPERTY(BlueprintReadOnly)
		UTankMovementComponent * TankMovement = nullptr;
	*/

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:

	UTankBarrel * Barrel = nullptr;

	// In seconds
	UPROPERTY(EditDefaultsOnly)
		float ReloadTime = 3.f;
	
	float LastTimeShot = -30.f;
};
