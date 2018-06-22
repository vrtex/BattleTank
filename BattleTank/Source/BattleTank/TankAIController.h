// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "BT_PlayerController.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Tank.h"
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

	ATank * GetControlledTank() const;

	ATank * GetPlayerTank() const;
	
	
};