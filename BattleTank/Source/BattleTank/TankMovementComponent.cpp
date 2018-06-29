// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"

UTankMovementComponent::UTankMovementComponent()
{
	UE_LOG(LogTemp, Warning, TEXT("Creating"));
}

void UTankMovementComponent::SetTracks(UTankTrack * Left, UTankTrack * Right)
{
	if(!Left || !Right)
	{
		UE_LOG(LogTemp, Error, TEXT("Give me tracks you idiot"));
		return;
	}
	LeftTrack = Left;
	RightTrack = Right;
}

void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if(!LeftTrack || !RightTrack)
		return;

	RightTrack->SetThrottle(Throw);
	LeftTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendMoveRight(float Throw)
{
	if(!LeftTrack || !RightTrack)
		return;

	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	FVector TankForwardDirection = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector TankIndendedDirection = MoveVelocity.GetSafeNormal();

	IntendMoveForward(FVector::DotProduct(TankForwardDirection, TankIndendedDirection));
	IntendMoveRight(FVector::CrossProduct(TankForwardDirection, TankIndendedDirection).Z);
}