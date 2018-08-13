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

void UTankAimingComponent::SetParts(UTankBarrel * Barrel, UTankTurret * Turret)
{
	if(!Barrel || !Turret)
	{
		UE_LOG(LogTemp, Warning, TEXT("Can't find parts"));
		FGenericPlatformMisc::RequestExit(false);
	}
	this->Barrel = Barrel;
	this->Turret = Turret;
}

int32 UTankAimingComponent::GetCurrentAmmo() const
{
	return CurrentAmmo;
}

// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();
	LastTimeShot = GetWorld()->GetTimeSeconds();
	CurrentAimState = EAimState::Reloading;
	bReloaded = false;
	//ReloadDelegate.BindUFunction(this, FName("Reload"));
	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &UTankAimingComponent::Reload, ReloadTime, false, -1.f);
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if(CurrentAmmo == 0)
		CurrentAimState = EAimState::NoAmmo;
	else if(!bReloaded)
		CurrentAimState = EAimState::Reloading;
	else if(bBarrelIsMoving)
		CurrentAimState = EAimState::Moving;
	else
		CurrentAimState = EAimState::Locked;
}

void UTankAimingComponent::SetLaunchSpeed(float NewSpeed)
{
	LaunchSpeed = NewSpeed;
}

void UTankAimingComponent::Fire()
{
	if(!Barrel)
		return;

	if(!ensure(ProjectileBlueprint))
		return;

	if(!ProjectileBlueprint)
		return;

	if(CurrentAimState == EAimState::Reloading || CurrentAimState == EAimState::NoAmmo)
		return;

	Barrel->Shoot(ProjectileBlueprint, LaunchSpeed);
	--CurrentAmmo;
	bReloaded = false;
	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &UTankAimingComponent::Reload, ReloadTime, false, -1.f);
}

void UTankAimingComponent::SetBarrelComponent(UTankBarrel * Component)
{
	Barrel = Component;
}

void UTankAimingComponent::SetTurretComponent(UTankTurret * Component)
{
	Turret = Component;
}

void UTankAimingComponent::AimAtLocation(const FVector & Target)
{
	if(!ensure(Barrel) || !ensure(Turret))
		return;
	

	FVector TossDirection;
	bool bGotSolution = UGameplayStatics::SuggestProjectileVelocity
	(
		this,
		TossDirection,
		Barrel->GetSocketLocation(FName("FiringPoint")), Target, LaunchSpeed,
		false,
		0.f,
		0.f,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);
	if(!bGotSolution)
	{
		return;
	}

	float BarrelPitch = Barrel->GetComponentRotation().Pitch;
	float TurretYaw = Turret->GetComponentRotation().Yaw;

	bBarrelIsMoving = true;
	MoveBarrel(TossDirection);
	MoveTurret(TossDirection);
	if(FMath::IsNearlyEqual(BarrelPitch, TossDirection.Rotation().Pitch, AimAccuracy) &&
		FMath::IsNearlyEqual(TurretYaw, TossDirection.Rotation().Yaw, AimAccuracy))
		bBarrelIsMoving = false;
}

bool UTankAimingComponent::isLocked() const
{
	return CurrentAimState == EAimState::Locked;
}

void UTankAimingComponent::MoveBarrel(const FVector & AimDirection)
{
	FRotator TargetRotation = AimDirection.Rotation();
	FRotator CurrentRotation = Barrel->GetForwardVector().Rotation();
	FRotator Delta = TargetRotation - CurrentRotation;

	if(FMath::Abs(Delta.Pitch) < AimAccuracy) return;
	Barrel->Elevate(Delta.Pitch);
}

void UTankAimingComponent::MoveTurret(const FVector & AimDirection)
{
	FRotator TargetRotation = AimDirection.Rotation();
	FRotator CurrentRotation = Turret->GetForwardVector().Rotation();
	FRotator Delta = TargetRotation - CurrentRotation;
	if(FMath::Abs(Delta .Yaw) > 180.f)
		Delta *= -1;
	
	if(FMath::Abs(Delta.Yaw) < AimAccuracy) return;

	Turret->Rotate(Delta.Yaw);
}

void UTankAimingComponent::Reload()
{
	UE_LOG(LogTemp, Warning, TEXT("Reloading"));
	bReloaded = true;
}