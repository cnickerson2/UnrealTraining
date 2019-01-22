// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

ATank* ATankAIController::GetAITank() const
{
    return Cast<ATank>(GetPawn());
}

ATank* ATankAIController::GetPlayerTank() const
{
    auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

    if(!PlayerPawn)
    {
        return nullptr;
    }

    return Cast<ATank>(PlayerPawn);
}

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();

    //ATank* AITank = GetAITank();
    //if (!AITank)
    //{
    //    UE_LOG(LogTemp, Warning, TEXT("No Tank is currently being Controlled by AI"))
    //}
    //else
    //{
    //    UE_LOG(LogTemp, Warning, TEXT("AI Tank Object: %s"), *AITank->GetName())
    //}

    ATank* PlayerTank = GetPlayerTank();

    if(!PlayerTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("No Player Tank was found"))
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Player Tank Object Found: %s"), *PlayerTank->GetName())
    }
}