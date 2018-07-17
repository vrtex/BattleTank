// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "CoreMinimal.h"
#include "AIController.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	GENERATED_BODY()
	

public:
	void BeginPlay() override;

	void virtual Tick(float DeltaSeconds) override;


	ATank * GetControlledTank() const;

	ATank * GetPlayerTank() const;
	
private:
	ATank * Controlled = nullptr;

	UPROPERTY(EditDefaultsOnly)
		float AcceptanceRadius = 3000;

};
