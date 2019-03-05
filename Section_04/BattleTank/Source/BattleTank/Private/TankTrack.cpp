// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle)
{
    Throttle = FMath::Clamp<float>(Throttle, -1, 1);
  


    auto ForceApplied = GetForwardVector() * Throttle * TrackMaxDrivingForce;

    auto ForceLocation = GetComponentLocation();

    auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
    TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

UTankTrack::UTankTrack()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UTankTrack::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime,TickType,ThisTickFunction);

    auto SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

    // Work-out the required acceleration this frame to correct
    auto CorrectionAcceleration = (-SlippageSpeed / DeltaTime) * GetRightVector();
    // Calculate & apply sideways force (F = m*a)
    auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
    auto CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; // Two Tracks

    TankRoot->AddForce(CorrectionForce);
}