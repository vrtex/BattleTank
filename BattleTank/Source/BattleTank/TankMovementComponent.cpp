// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"

UTankMovementComponent::UTankMovementComponent()
{
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

void UTankMovementComponent::SetDirection(float Forward, float Right)
{
	if(!LeftTrack || !RightTrack)
		return;


	CurrentDirection = FVector(Right, 0, Forward);
	//CurrentDirection = FVector(Forward, Right, 0);
	/*
	Forward /= 2;
	Right /= 2;
	LeftTrack->SetThrottle(FMath::Sin(CurrentDirection.Rotation().Yaw));
	RightTrack->SetThrottle(-FMath::Sin(CurrentDirection.Rotation().Yaw));
	*/

	float Force = CurrentDirection.Size();
	float ForwardForce = FVector::DotProduct(FVector(0, 0, 1), CurrentDirection) * Force;
	float RightForce = FVector::DotProduct(FVector(1, 0, 0), CurrentDirection) * Force;

	LeftTrack->SetThrottle(RightForce + ForwardForce);
	RightTrack->SetThrottle(-RightForce + ForwardForce);
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	FVector TankForwardDirection = GetOwner()->GetActorForwardVector().GetSafeNormal();
	FVector TankIndendedDirection = MoveVelocity.GetSafeNormal();

	IntendMoveForward(FVector::DotProduct(TankForwardDirection, TankIndendedDirection));
	IntendMoveRight(FVector::CrossProduct(TankForwardDirection, TankIndendedDirection).Z);
}