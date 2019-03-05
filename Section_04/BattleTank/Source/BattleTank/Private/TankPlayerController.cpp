// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"


//Get world location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
    // Find the crosshair position
    int32 ViewportSizeX, ViewportSizeY;
    GetViewportSize(ViewportSizeX, ViewportSizeY);
    auto ScreenLocation = FVector2D(ViewportSizeX * CrosshairXLocation, ViewportSizeY * CrosshairYLocation);

    // "De-project" the screen position of the crosshair to a world direction
    FVector LookDirection;
    if(GetLookDirection(ScreenLocation,LookDirection))
    {
        // Line-trace along that look direction, and see what we hit (up to max range)
        if(GetLookVectorHitLocation(LookDirection,OutHitLocation))
        {
            return true; // We successfully got a hit.
        }
    }   

    return false; // We did not get a hit.
}

bool ATankPlayerController::GetLookVectorHitLocation(const FVector& LookDirection, FVector& HitLocation) const
{
    FHitResult HitResult;

    auto StartLocation = PlayerCameraManager->GetCameraLocation();
    auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

    if(GetWorld() -> 
            LineTraceSingleByChannel
            (
                HitResult,
                StartLocation,
                EndLocation,
                ECollisionChannel::ECC_Visibility)
        ) // Line Trace Succeeds
    {
        // Set hit location
        HitLocation = HitResult.Location;
        return true;
    }
    HitLocation = FVector(0);
    return false;
}

void ATankPlayerController::BeginPlay()
{
    Super::BeginPlay();

    auto ControlledTank = GetPawn();
    if (!ensure(ControlledTank))
    {
        return;
    }

    auto AimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
    if(ensure(AimingComponent))
    {
        FoundAimingComponent(AimingComponent);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Player controller can't find aiming component at Begin Play"));
    }
}

bool ATankPlayerController::GetLookDirection(const FVector2D& ScreenLocation, FVector& LookDirection) const
{
    
    FVector WorldLocation;
    return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, LookDirection);
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair()
{
    if (!GetPawn()) { return; } // e.g. if not possessing
    auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
    if (!ensure(AimingComponent)) { return; }

    FVector HitLocation; //Out Parameter
    if (GetSightRayHitLocation(HitLocation)) // Has a "side-effect", is going to line trace
    {
        AimingComponent->AimAt(HitLocation);
    }


}
