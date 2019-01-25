// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true; // TODO: Should this really tick?

    // ...
}


void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
    Barrel = BarrelToSet;
}



// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
    Super::BeginPlay();

    // ...

}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // ...
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
    if (!Barrel) { return; }

    FVector OutLaunchVelocity(0);
    FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

    // Calculate the OutLaunchVelocity
    if(UGameplayStatics::SuggestProjectileVelocity
        (this, 
        OutLaunchVelocity, 
        StartLocation, 
        HitLocation, 
        LaunchSpeed,
        false,
        0,
        0,
        ESuggestProjVelocityTraceOption::DoNotTrace)
    )
    {
        auto AimDirection = OutLaunchVelocity.GetSafeNormal();
        MoveBarrel(AimDirection);
    }
    else
    {
        // If no solution found, do nothing

    }
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
    // Get the Rotation of the Aiming Vector
    auto BarrelRotator = Barrel->GetForwardVector().Rotation();
    auto AimAsRotator = AimDirection.Rotation();
    auto DeltaRotator = AimAsRotator - BarrelRotator;

    // Set the Barrel to the rotation determined above
    Barrel->Elevate(DeltaRotator.Pitch); 
}

