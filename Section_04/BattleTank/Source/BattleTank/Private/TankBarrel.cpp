// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
    // Move the Barrel the right amount this frame
    // Give a max elevation speed and the frame time
    auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
    auto RawNewElevation = RelativeRotation.Pitch + ElevationChange;
    auto Elevation = FMath::Clamp<float>(RawNewElevation, MinElevationInDegress, MaxElevationInDegrees);
    SetRelativeRotation(FRotator(Elevation, 0, 0));
}
