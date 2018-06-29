// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "TankTrack.h"
#include "CoreMinimal.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

/**
 * Fly-by-Wire controls
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent) )
class BATTLETANK_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:
	UTankMovementComponent();

	UFUNCTION(BlueprintCallable, Category = Setup)
		void SetTracks(UTankTrack * Left, UTankTrack * Right);

	UFUNCTION(BlueprintCallable, Category = Movement)
		void IntendMoveForward(float Throw);

	UFUNCTION(BlueprintCallable, Category = Movement)
		void IntendMoveRight(float Throw);

private:

	void RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed) override;

protected:

private:
	
	UTankTrack * LeftTrack = nullptr, * RightTrack = nullptr;
};
