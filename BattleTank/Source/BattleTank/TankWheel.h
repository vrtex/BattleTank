// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/PhysicsEngine/PhysicsConstraintComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"
#include "Components/SceneComponent.h"
#include "TankWheel.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankWheel : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankWheel();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		

protected:

public:

	UPROPERTY(VisibleAnywhere)
		UPhysicsConstraintComponent * Spring = nullptr;

	UPROPERTY(VisibleAnywhere)
		UPhysicsConstraintComponent * WheelAxle = nullptr;

	UPROPERTY(VisibleAnywhere)
		USphereComponent * Axle = nullptr;

	UPROPERTY(VisibleAnywhere)
		USphereComponent * Wheel = nullptr;

	UPROPERTY(EditAnywhere, Category = "Setup")
		float SpringStrength = 750.f;

	UPROPERTY(EditAnywhere, Category = "Setup")
		float SpringStiffness = 15.f;

	UPROPERTY(EditAnywhere, Category = "Setup")
		float SpringGive = 50;

	UPROPERTY(EditAnywhere, Category = "Setup")
		float WheelOffset = -170.f;

	UPROPERTY(EditAnywhere, Category = "Setup")
		float WheelMass = 1000.f;

private:
	void SetupSpring();

};
