// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "BT_PlayerController.generated.h"


/**
 * 
 */
UCLASS()
class BATTLETANK_API ABT_PlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void virtual BeginPlay() override;

	void virtual Tick(float DeltaSeconds) override;
	

	ATank * GetControlledTank() const;
	
private:
	void AimTowardsCrosshair();
	
	bool GetSightRayHitLocation(FVector & HitLocaton) const;

	UPROPERTY(EditAnywhere)
		float CrosshairLocationX = 0.5f;

	UPROPERTY(EditAnywhere)
		float CrosshairLocationY = 0.333f;
};
