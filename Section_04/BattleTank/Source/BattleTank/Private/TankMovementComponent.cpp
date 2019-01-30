// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"

void UTankMovementComponent::IntendMoveForward(float Throw)
{
    RightTrack->SetThrottle(Throw);
    LeftTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
    RightTrack->SetThrottle(-Throw);
    LeftTrack->SetThrottle(Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
    auto AIForwardIntention = MoveVelocity.GetSafeNormal();
    auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();

    auto ForwardThrow = FVector::DotProduct(AIForwardIntention, TankForward);
    IntendMoveForward(ForwardThrow);
}

void UTankMovementComponent::Initialize(UTankTrack* LeftTrackToSet, UTankTrack* RightTrackToSet)
{
    if (!LeftTrackToSet || !RightTrackToSet) { return; }

    RightTrack = RightTrackToSet;
    LeftTrack = LeftTrackToSet;
    // TODO: Prevent double use with Triggers
}
