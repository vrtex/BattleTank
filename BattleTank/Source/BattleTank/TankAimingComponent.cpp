// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::SetBarrelComponent(UTankBarrel * Component)
{
	Barrel = Component;
}

void UTankAimingComponent::SetTurretComponent(UStaticMeshComponent * Component)
{
	Turret = Component;
}

void UTankAimingComponent::AimAtLocation(const FVector & Target, const float Speed)
{
	if(!Barrel || !Turret)
		return;

	FVector TossDirection;
	bool bGotSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		TossDirection,
		Barrel->GetSocketLocation(FName("FiringPoint")), Target, Speed,
		false,
		0.f,
		0.f,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if(!bGotSolution)
	{
		return;
	}

	FRotator Direction = TossDirection.Rotation();
	//return;

	FRotator TurretDirection(0, Direction.Yaw, 0);
	Turret->SetWorldRotation(TurretDirection);
	MoveBarrel(TossDirection);
	//Barrel->SetRelativeRotation(BarrelDirection);
}

void UTankAimingComponent::MoveBarrel(const FVector & AimDirection)
{
	FRotator TargetRotation = AimDirection.Rotation();
	FRotator CurrentRotation = Barrel->GetForwardVector().Rotation();
	FRotator Delta = TargetRotation - CurrentRotation;

	Barrel->Elevate(Delta.Pitch);

}