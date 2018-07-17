// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"


UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
	CurrentThrottle = 0.f;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();

	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::ApplySidewaysForce()
{
	UStaticMeshComponent * TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());

	FVector CorrectionAcceleration = -FVector::DotProduct(GetRightVector(), GetComponentVelocity()) / GetWorld()->GetDeltaSeconds() * GetRightVector();

	FVector CorrectionForce = CorrectionAcceleration * TankRoot->GetMass() / 2;

	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1.f, 1.f);
	CurrentThrottle = Throttle;
}

void UTankTrack::DriveTrack()
{
	UE_LOG(LogTemp, Warning, TEXT("%f"), CurrentThrottle);
	FVector ForceApplied = GetForwardVector() * Power * CurrentThrottle;
	FVector Location = GetComponentLocation();
	USceneComponent * TankRoot = GetOwner()->GetRootComponent();
	Cast<UPrimitiveComponent>(TankRoot)->AddForceAtLocation(ForceApplied, Location);
}

void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	DriveTrack();
	ApplySidewaysForce();
}