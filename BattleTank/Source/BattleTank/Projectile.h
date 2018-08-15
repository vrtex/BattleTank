// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Runtime/Engine/Classes/Components/PrimitiveComponent.h"
#include "Runtime/Engine/Classes/GameFramework/ProjectileMovementComponent.h"
#include "Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/PhysicsEngine/RadialForceComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	// virtual void Tick(float DeltaTime) override;

	void Launch(float Speed);

private:

	UFUNCTION()
		void OnHit(AActor * SelfActor, AActor * OtherActor, FVector NormalImpulse, const FHitResult & Hit);

	UFUNCTION()
		void DestroySelf();

	FTimerHandle DestroyTimer;

protected:
	UPROPERTY(EditDefaultsOnly)
		float DestroyDelay = 1.f;
private:

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
		float BaseDamage = 10.f;

	UProjectileMovementComponent * ProjectileMovement = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Collision")
		UStaticMeshComponent * CollisionMesh = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Particle")
		UParticleSystemComponent * LaunchBlast = nullptr;


	UPROPERTY(VisibleAnywhere, Category = "Particle")
		UParticleSystemComponent * ImpactBlast = nullptr;


	UPROPERTY(VisibleAnywhere, Category = "Force")
		URadialForceComponent * Explosion = nullptr;

};
