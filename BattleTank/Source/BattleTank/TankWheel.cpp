// Fill out your copyright notice in the Description page of Project Settings.

#include "TankWheel.h"


// Sets default values for this component's properties
UTankWheel::UTankWheel()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
	Spring = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Spring"));

	Axle = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
	Axle->AttachToComponent(Spring, FAttachmentTransformRules::KeepRelativeTransform);
	Axle->SetSimulatePhysics(true);
	Axle->SetRelativeLocation(FVector(0, 0, WheelOffset));
	Axle->SetMobility(EComponentMobility::Movable);

	Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	Wheel->AttachToComponent(Axle, FAttachmentTransformRules::KeepRelativeTransform);
	Wheel->SetSimulatePhysics(true);
	Wheel->SetRelativeLocation(FVector(0, 0, WheelOffset));
	Wheel->SetMobility(EComponentMobility::Movable);



	WheelAxle = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Wheel Axle"));
	WheelAxle->SetupAttachment(Axle);
}


// Called when the game starts
void UTankWheel::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankWheel::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankWheel::SetupSpring()
{
	Spring->SetAngularSwing1Limit(EAngularConstraintMotion::ACM_Locked, 0);
	Spring->SetAngularSwing2Limit(EAngularConstraintMotion::ACM_Locked, 0);
	Spring->SetAngularTwistLimit(EAngularConstraintMotion::ACM_Locked, 0);

	Spring->SetLinearXLimit(ELinearConstraintMotion::LCM_Locked, 0);
	Spring->SetLinearYLimit(ELinearConstraintMotion::LCM_Locked, 0);
	Spring->SetLinearZLimit(ELinearConstraintMotion::LCM_Limited, SpringGive);

	Spring->SetLinearPositionTarget(FVector(0, 0, 0));
	Spring->SetLinearPositionDrive(false, false, true);
	Spring->SetLinearVelocityTarget(FVector(0, 0, 0));
	Spring->SetLinearVelocityDrive(false, false, true);
	Spring->SetLinearDriveParams(SpringStrength, SpringStiffness, 0);


	WheelAxle->SetConstrainedComponents(
		Cast<UPrimitiveComponent>(Axle),
		NAME_None,
		Cast<UPrimitiveComponent>(Wheel),
		NAME_None
	);
}
