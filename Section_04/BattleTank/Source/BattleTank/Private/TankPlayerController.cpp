// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();

    ATank* ControlledTank = GetControlledTank();
    if(!ControlledTank)
    {
        UE_LOG(LogTemp, Warning, TEXT("No Tank is currently being Controlled"));
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Controlled Tank Object: %s"), *ControlledTank->GetName());
    }
    
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
    if (!GetControlledTank()) { return; }

    // Get world location if linetrace through crosshair
    // if it hits the landscape
        // Tell controlled tank to aim at this point
}
