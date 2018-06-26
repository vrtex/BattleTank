// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"



void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	Controlled = GetControlledTank();
	if(Controlled)
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Controlling tank %s"), *Controlled->GetName());
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("No tank controlled by AI"));
	}

	if(!GetPlayerTank())
		UE_LOG(LogTemp, Error, TEXT("Can't find player tank"));

}

void ATankAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if(!GetPlayerTank()) return;
	Controlled->AimAtLocation(GetPlayerTank()->GetActorLocation());

	Controlled->Fire();
}


ATank * ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	auto Pawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if(!Pawn) return nullptr;
	return Cast<ATank>(Pawn);
}