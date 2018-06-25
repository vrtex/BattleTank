// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
// sdd

#include "TankBarrel.h"
#include "TankAimingComponent.h"
#include "Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	void AimAtLocation(const FVector & Target);

	UFUNCTION(Blueprintcallable, Category = Setup)
		void SetBarrelComponent(UTankBarrel * Component);

	UFUNCTION(Blueprintcallable, Category = Setup)
		void SetTurretComponent(UStaticMeshComponent * Component);
	
	UPROPERTY(EditAnywhere, Category = Firing)
		float LaunchSpeed = 10000.f; // TODO: find value that works

	/*
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UStaticMeshComponent * TurretComponent;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		UStaticMeshComponent * Turret;
	*/

	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UTankAimingComponent * TankAimingComponent = nullptr;

public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};
