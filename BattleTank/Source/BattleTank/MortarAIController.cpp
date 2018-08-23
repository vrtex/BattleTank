// Fill out your copyright notice in the Description page of Project Settings.

#include "MortarAIController.h"




void AMortarAIController::BeginPlay()
{
	Super::BeginPlay();

	Controlled = GetControlledMortart();
	if(!Controlled)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find controlled mortar"));
	}
}

void AMortarAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if(!Controlled || !GetPlayerTank())
		return;

	Controlled->AimAtLocation(GetPlayerTank()->GetActorLocation());

	if(Controlled->isLocked())
		Controlled->Fire();
}

void AMortarAIController::SetPawn(APawn * NewPawn)
{
	Super::SetPawn(NewPawn);

	if(!NewPawn)
		return;

	AMortar * ControlledMortar = Cast<AMortar>(NewPawn);
	Controlled = ControlledMortar;
	if(!ControlledMortar) return;

	Controlled->OnDeath.AddUniqueDynamic(this, &AMortarAIController::OnMortartDeath);
}

AMortar * AMortarAIController::GetControlledMortart() const
{
	return Cast<AMortar>(GetPawn());
}

ATank * AMortarAIController::GetPlayerTank()
{
	auto Pawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if(!Pawn) return nullptr;
	return Cast<ATank>(Pawn);
}

void AMortarAIController::OnMortartDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("Mortar ded"));
}