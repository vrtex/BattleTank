// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"




void UTankTrack::SetThrottle(float Throttle)
{
	Throttle = FMath::Clamp(Throttle, -1.f, 1.f);
	FVector ForceApplied = GetForwardVector() * Power * Throttle;
	FVector Location = GetComponentLocation();
	USceneComponent * TankRoot = GetOwner()->GetRootComponent();
	if(!TankRoot)
		return;
	Cast<UPrimitiveComponent>(TankRoot)->AddForceAtLocation(ForceApplied, Location);
	// TODO: clamp this shit
}