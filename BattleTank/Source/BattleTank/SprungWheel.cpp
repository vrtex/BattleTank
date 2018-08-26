// Fill out your copyright notice in the Description page of Project Settings.

#include "SprungWheel.h"


// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SetTickGroup(ETickingGroup::TG_PostPhysics);

	Spring = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Spring"));
	SetRootComponent(Spring);

	Axle = CreateDefaultSubobject<USphereComponent>(FName("Axle"));
	Axle->AttachToComponent(Spring, FAttachmentTransformRules::KeepRelativeTransform);
	Axle->SetSimulatePhysics(true);
	Axle->SetRelativeLocation(FVector(0, 0, WheelOffset));
	Axle->SetMobility(EComponentMobility::Movable);

	Wheel = CreateDefaultSubobject<USphereComponent>(FName("Wheel"));
	Wheel->AttachToComponent(Axle, FAttachmentTransformRules::KeepRelativeTransform);
	Wheel->SetSimulatePhysics(true);
	Wheel->SetRelativeLocation(FVector(0, 0, 0));
	Wheel->SetMobility(EComponentMobility::Movable);

	WheelAxle = CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Wheel Axle"));
	WheelAxle->SetupAttachment(Axle);
}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();


	Wheel->SetNotifyRigidBodyCollision(true);
	Wheel->OnComponentHit.AddDynamic(this, &ASprungWheel::OnHit);

	SetupSpring();
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if(GetWorld()->TickGroup != ETickingGroup::TG_PostPhysics)
		return;
	CurrentForce = 0;
}

void ASprungWheel::AddForce(float Magnitude)
{
	Wheel->AddForce(Axle->GetForwardVector() * Magnitude);
}

void ASprungWheel::SetThrottle(float Throttle)
{
	CurrentForce = Throttle * MaxSpeed * 600000;
}

void ASprungWheel::SetupSpring()
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

	if(!Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent()))
		return;
	Spring->SetConstrainedComponents(
		Cast<UPrimitiveComponent>(GetAttachParentActor()->GetRootComponent()),
		NAME_None,
		Cast<UPrimitiveComponent>(Axle),
		NAME_None
	);

	WheelAxle->SetConstrainedComponents(
		Cast<UPrimitiveComponent>(Axle),
		NAME_None,
		Cast<UPrimitiveComponent>(Wheel),
		NAME_None
	);
	//Spring->ComponentName1.ComponentName = FName(*Wheel->GetName());

}

void ASprungWheel::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	AddForce(CurrentForce);
}