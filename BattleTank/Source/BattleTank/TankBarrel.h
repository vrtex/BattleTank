// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Runtime/Engine/Classes/Engine/StaticMeshSocket.h"
#include "Projectile.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
	
public:
	void Elevate(float RelativeSpeed);

	void Shoot(TSubclassOf<AProjectile> ProjectileClass, float Speed) const;

private:
	UPROPERTY(EditDefaultsOnly)
		float MaxSpeed = 10.f;
	
	UPROPERTY(EditDefaultsOnly)
		float MinElevation = -3.f;

	UPROPERTY(EditDefaultsOnly)
		float MaxElevation = 35.f;

};
