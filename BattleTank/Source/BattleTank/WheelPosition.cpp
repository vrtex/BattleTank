// Fill out your copyright notice in the Description page of Project Settings.

#include "WheelPosition.h"
#include "TankTrack.h"


// Sets default values for this component's properties
UWheelPosition::UWheelPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UWheelPosition::BeginPlay()
{
	Super::BeginPlay();

	ASprungWheel * Wheel = GetWorld()->SpawnActorDeferred<ASprungWheel>(
		WheelClass.Get(),
		GetComponentTransform()
		);
	if(!Wheel)
		return;
	Wheel->AttachToComponent(GetAttachParent(), FAttachmentTransformRules::KeepWorldTransform);
	UGameplayStatics::FinishSpawningActor(Wheel, GetComponentTransform());

	if(!Cast<UTankTrack>(GetAttachParent()))
		return;
	Cast<UTankTrack>(GetAttachParent())->AddWheel(Wheel);
}


// Called every frame
void UWheelPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

