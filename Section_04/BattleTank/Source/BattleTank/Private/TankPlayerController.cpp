// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"

ATank* ATankPlayerController::GetControlledTank() const
{
    return Cast<ATank>(GetPawn());
}

//Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
    // Find the crosshair position
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);

    auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);
    // "De-project" the screen position of the crosshair to a world direction
    // Line-trace along that look direction, and see what we hit (up to max range)
    return true;
}

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();

    ATank* ControlledTank = GetControlledTank();
    if (!ControlledTank)
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

    FVector HitLocation; //Out Parameter
    if (GetSightRayHitLocation(HitLocation)) // Has a "side-effect", is going to line trace
    {

        // TODO: Tell controlled tank to aim at this point
    }


}
