// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = false;

    // ...
}


void UTankAimingComponent::SetBarrelReference(UTankBarrel* BarrelToSet)
{
    if(!BarrelToSet)
    {
        UE_LOG(LogTemp, Error, TEXT("Barrel has not been set in BP"));
        return;
    }
    Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTankTurret* TurretToSet)
{
    if (!TurretToSet)
    {
        UE_LOG(LogTemp, Error, TEXT("Turret has not been set in BP"));
        return;
    }
    Turret = TurretToSet;
}



// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
    Super::BeginPlay();

    // ...

}


void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
    if (!Barrel || !Turret) { return; }

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
    auto AimAsRotator = AimDirection.Rotation();

    // Get the Rotation of the Aiming Vector
    auto BarrelRotator = Barrel->GetForwardVector().Rotation();
    auto DeltaBarrelRotator = AimAsRotator - BarrelRotator;

    auto TurretRotator = Turret->GetForwardVector().Rotation();
    auto DeltaTurretRotator = AimAsRotator - TurretRotator;
    // Set the Barrel to the rotation determined above
    Barrel->Elevate(DeltaBarrelRotator.Pitch);
    Turret->Rotate(DeltaTurretRotator.Yaw);
}

