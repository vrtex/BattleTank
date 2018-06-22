// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"



void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	if(GetControlledTank())
	{
		UE_LOG(LogTemp, Warning, TEXT("AI Controlling tank %s"), *GetControlledTank()->GetName());

	}
	else
		UE_LOG(LogTemp, Error, TEXT("No tank controlled by AI"));

	if(!GetPlayerTank())
		UE_LOG(LogTemp, Error, TEXT("Can't find player tank"));

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