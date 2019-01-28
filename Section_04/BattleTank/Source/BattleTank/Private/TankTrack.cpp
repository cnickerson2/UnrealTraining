// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
    Throttle = FMath::Clamp<float>(Throttle, -1, 1);
    UE_LOG(LogTemp, Warning, TEXT("%s throttle: %f"), *GetName(), Throttle);
}
