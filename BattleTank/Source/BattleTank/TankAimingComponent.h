// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TankTurret.h"
#include "TankBarrel.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "CoreMinimal.h"
#include "Projectile.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EAimState : uint8
{
	Reloading,
	Moving,
	Locked,
	NoAmmo
};

// Handles aiming by manipulating barrel and turret
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTankAimingComponent();

	void SetLaunchSpeed(float NewSpeed);

	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetParts(UTankBarrel * Barrel, UTankTurret * Turret);

	UFUNCTION(BlueprintCallable)
		int32 GetCurrentAmmo() const;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
		EAimState CurrentAimState = EAimState::Moving;

	UPROPERTY(EditAnywhere)
		TSubclassOf<AProjectile> ProjectileBlueprint;
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Fire();
	
		
	void SetBarrelComponent(UTankBarrel * Component);

	void SetTurretComponent(UTankTurret * Component);

	void AimAtLocation(const FVector & Target);

	bool isLocked() const;

private:

	void MoveBarrel(const FVector & AimDirection);

	void MoveTurret(const FVector & AimDirection);

	float AimAccuracy = 1.f;

	UTankBarrel * Barrel = nullptr;

	UTankTurret * Turret = nullptr;

	float LaunchSpeed = 8000.f;

	float LastTimeShot;

	bool bBarrelIsMoving;

	bool bReloaded;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float ReloadTime = 3.f;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		int32 CurrentAmmo = 3;

	FTimerHandle ReloadTimer;

	UFUNCTION()
		void Reload();
};
