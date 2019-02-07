// Fill out your copyright notice in the Description page of Project Settings.


#include "TankAimingComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    // off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = false;

    // ...
}

void UTankAimingComponent::BeginPlay()
{
    Super::BeginPlay();
    // So first fire is after initial reload
    LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::Initialize(UTankTurret* TurretToSet, UTankBarrel* BarrelToSet)
{
    if (!(TurretToSet && BarrelToSet)) { return; }

    Turret = TurretToSet;
    Barrel = BarrelToSet;
}


void UTankAimingComponent::AimAt(FVector HitLocation)
{
    if (!ensure(Barrel && Turret)) {  return; }
    
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

void UTankAimingComponent::Fire()
{

    if(FiringStatus != EFiringStatus::Reloading)
    {
        if (ensure(Barrel) && ensure(ProjectileBlueprint))
        {
            // Spawn a projectile at the barrel location
            auto Projectile = GetWorld()->SpawnActor<AProjectile>(
                ProjectileBlueprint,
                Barrel->GetSocketLocation(FName("Projectile")),
                Barrel->GetSocketRotation(FName("Projectile"))
                );

            Projectile->LaunchProjectile(LaunchSpeed);
            LastFireTime = FPlatformTime::Seconds();
        }
    }
}

void UTankAimingComponent::MoveBarrel(FVector AimDirection)
{
    if (!ensure(Barrel && Turret)) { return; }

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

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    if ((FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds)
    {
        FiringStatus = EFiringStatus::Reloading;
    }
}

void UTankAimingComponent::SetProjectileBlueprint(TSubclassOf<AProjectile> ProjectileBluePrintToSet)
{
    ProjectileBlueprint = ProjectileBluePrintToSet;
}

