// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"



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
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}