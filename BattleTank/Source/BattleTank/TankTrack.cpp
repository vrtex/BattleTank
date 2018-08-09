// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"


UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = true;

}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();

	//DriveCollision->OnComponentHit.__Internal_AddDynamic(this, &UTankTrack::OnHit, FName("KROWA"));
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	FHitResult HitResult;
	FVector TraceEnd = GetSocketLocation(FName("Drive Socket"));
	if(

		GetWorld()->SweepTestByChannel(
			GetComponentLocation(),
			TraceEnd,
			FQuat(),
			ECollisionChannel::ECC_WorldStatic,
			FCollisionShape::MakeBox(GetComponentLocation() - TraceEnd)
		))

	{
		DriveTrack();
	}
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
	CurrentThrottle = Throttle;

}

void UTankTrack::DriveTrack()
{
	UE_LOG(LogTemp, Warning, TEXT("%f throttle is: %f"), GetWorld()->GetTimeSeconds(), CurrentThrottle);
	FVector ForceApplied = GetForwardVector() * Power * CurrentThrottle;
	FVector Location = GetComponentLocation();
	USceneComponent * TankRoot = GetOwner()->GetRootComponent();
	Cast<UPrimitiveComponent>(TankRoot)->AddForceAtLocation(ForceApplied, Location);
}

void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("%f HUEHUHEU"), GetWorld()->GetTimeSeconds());
	DriveTrack();
	ApplySidewaysForce();
}