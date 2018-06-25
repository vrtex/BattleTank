// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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

private:
	UPROPERTY(EditAnywhere)
		float MaxSpeed = 10.f;
	
	UPROPERTY(EditAnywhere)
		float MinElevation = -3.f;

	UPROPERTY(EditAnywhere)
		float MaxElevation = 35.f;

};
