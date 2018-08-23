// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"
#include "Runtime/Core/Public/Containers/Array.h"


UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;

	//Wheel = CreateDefaultSubobject<UTankWheel>(FName("Wheel"));
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();

	//DriveCollision->OnComponentHit.__Internal_AddDynamic(this, &UTankTrack::OnHit, FName("KROWA"));
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
	/*
	ASprungWheel * NewWheel = GetWorld()->SpawnActorDeferred<ASprungWheel>(WheelClass.Get(), GetComponentTransform());
	NewWheel->AttachToComponent(this, FAttachmentTransformRules::KeepRelativeTransform);
	UGameplayStatics::FinishSpawningActor(NewWheel, GetComponentTransform());
	*/
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

	for(auto W : Wheels)
		W->SetThrottle(Throttle);
	
}

void UTankTrack::DriveTrack()
{
	FVector ForceApplied = GetForwardVector() * Power * CurrentThrottle;

	for(auto W : Wheels)
		W->AddForce(CurrentThrottle);
	/*
	FVector Location = GetComponentLocation();
	USceneComponent * TankRoot = GetOwner()->GetRootComponent();
	Cast<UPrimitiveComponent>(TankRoot)->AddForceAtLocation(ForceApplied, Location);
	*/
}

void UTankTrack::AddWheels(TArray<ASprungWheel*> ToAdd)
{
	for(auto W : ToAdd)
		AddWheel(W);
}

void UTankTrack::AddWheel(ASprungWheel * ToAdd)
{
	Wheels.Add(ToAdd);
}

TArray<ASprungWheel*> UTankTrack::GetWheels() const
{
	return TArray<ASprungWheel*>();
}

void UTankTrack::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	DriveTrack();
	ApplySidewaysForce();

	CurrentThrottle = 0;
}