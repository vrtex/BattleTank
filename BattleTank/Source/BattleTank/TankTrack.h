// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "TankTrack.generated.h"

/**
 * Handles driving
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	UTankTrack();

	void BeginPlay() override;

	void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction) override;

	UFUNCTION(BlueprintCallable, Category = Movement)
	void SetThrottle(float Throttle);

	void DriveTrack();

	
private:

	float CurrentThrottle = 0.f;

	void ApplySidewaysForce();

	// Force applied to tank
	UPROPERTY(EditAnywhere)
		float Power = 40000000.f; // TODO does this work?

	UFUNCTION()
		void OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit);
	
};
