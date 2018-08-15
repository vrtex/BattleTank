// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Projectile Movement"));
	ProjectileMovement->bAutoActivate = false;

	CollisionMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("Collision mesh"));
	SetRootComponent(CollisionMesh);
	CollisionMesh->SetNotifyRigidBodyCollision(true);
	CollisionMesh->SetVisibility(false);

	LaunchBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Launch Blast"));
	LaunchBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);

	ImpactBlast = CreateDefaultSubobject<UParticleSystemComponent>(FName("Impact Blast"));
	ImpactBlast->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	ImpactBlast->bAutoActivate = false;

	Explosion = CreateDefaultSubobject<URadialForceComponent>(FName("Impact Force"));
	Explosion->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	Explosion->SetRelativeLocation(FVector(0));
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	OnActorHit.AddDynamic(this, &AProjectile::OnHit);
}

/*
// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
*/

void AProjectile::Launch(float Speed)
{
	
	if(ProjectileMovement == nullptr) return;
	ProjectileMovement->SetVelocityInLocalSpace(FVector(Speed, 0, 0));
	ProjectileMovement->bShouldBounce = true;
	ProjectileMovement->Activate();
}

void AProjectile::OnHit(AActor * SelfActor, AActor * OtherActor, FVector NormalImpulse, const FHitResult & Hit)
{
	LaunchBlast->Deactivate();
	ImpactBlast->Activate();

	Explosion->FireImpulse();

	SetRootComponent(ImpactBlast);
	CollisionMesh->DestroyComponent();

	UGameplayStatics::ApplyRadialDamage(
		this,
		BaseDamage,
		GetActorLocation(),
		Explosion->Radius,
		UDamageType::StaticClass(),
		TArray<AActor *>()
		);

	GetWorld()->GetTimerManager().SetTimer(DestroyTimer, this, &AProjectile::DestroySelf, DestroyDelay, false);
}

void AProjectile::DestroySelf()
{
	Destroy();
}