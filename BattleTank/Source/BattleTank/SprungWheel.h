// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/PhysicsEngine/PhysicsConstraintComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"
#include "SprungWheel.generated.h"

UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASprungWheel();

	virtual void Tick(float DeltaTime) override;

	void AddForce(float Magnitude);

	void SetThrottle(float Throttle);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

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

	UPROPERTY(EditAnywhere, Category = "Setup")
		float Torque = 300.f;
	
	UPROPERTY(EditAnywhere, Category = "Setup")
		float MaxSpeed = 25.f;

private:
	void SetupSpring();

	UFUNCTION()
		void OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit);

	float CurrentForce = 0.f;
};
