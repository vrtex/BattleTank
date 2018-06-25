// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Runtime/Engine/Public/DrawDebugHelpers.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
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
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CrosshairLocationX = 0.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float CrosshairLocationY = 0.333f;
private:
	void AimTowardsCrosshair();
	
	bool GetSightRayHitLocation(FVector & HitLocaton) const;

	void GetWorldDirection(FVector2D ScreenLocation, FVector & WorldDirection) const;


	UPROPERTY(EditAnywhere)
		float AimRange = 1000000.f;
};
