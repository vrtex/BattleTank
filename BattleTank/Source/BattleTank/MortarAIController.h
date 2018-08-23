// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "Mortar.h"
#include "Tank.h"
#include "CoreMinimal.h"
#include "MortarAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANK_API AMortarAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	void virtual BeginPlay() override;

	void virtual Tick(float DeltaSeconds) override;

	virtual void SetPawn(APawn * NewPawn) override;
	
	AMortar * GetControlledMortart() const;

private:
	AMortar * Controlled = nullptr;
	
	ATank * GetPlayerTank();

	UFUNCTION()
		void OnMortartDeath();
	
	
};
