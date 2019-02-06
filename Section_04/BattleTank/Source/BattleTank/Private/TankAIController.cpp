// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);


    auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
    auto AIAimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

    if (ensure(PlayerTank && AIAimingComponent))
    {
        MoveToActor(PlayerTank, AcceptanceRadius);

        AIAimingComponent->AimAt(PlayerTank->GetActorLocation());

        AIAimingComponent->Fire();
    }
}