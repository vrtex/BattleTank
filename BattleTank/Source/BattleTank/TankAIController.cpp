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

	MoveToActor(GetPlayerTank(), AcceptanceRadius, true, true, false);

	Controlled->AimAtLocation(GetPlayerTank()->GetActorLocation());

	if(Controlled->isLocked())
		Controlled->Fire();

}

void ATankAIController::SetPawn(APawn * NewPawn)
{
	Super::SetPawn(NewPawn);

	if(!NewPawn)
		return;

	ATank * PossesedTank = Cast<ATank>(NewPawn);
	Controlled = PossesedTank;
	if(!ensure(PossesedTank))
		return;

	// listen for death
	PossesedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
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

void ATankAIController::OnTankDeath()
{
	UE_LOG(LogTemp, Error, TEXT("DED"));
	if(!GetPawn())
		return;
	Controlled->DetachFromControllerPendingDestroy();
}