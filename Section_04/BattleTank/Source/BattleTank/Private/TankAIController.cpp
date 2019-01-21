// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

ATank* ATankAIController::GetAITank() const
{
    return Cast<ATank>(GetPawn());
}

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();

    ATank* AITank = GetAITank();
    if (!AITank)
    {
        UE_LOG(LogTemp, Warning, TEXT("No Tank is currently being Controlled by AI"))
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("AI Tank Object: %s"), *AITank->GetName())
    }

}