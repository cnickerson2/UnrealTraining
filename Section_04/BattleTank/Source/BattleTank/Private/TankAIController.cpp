// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);


    auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
    auto ThisAITank = Cast<ATank>(GetPawn());

    if (PlayerTank && ThisAITank)
    {
        MoveToActor(PlayerTank, AcceptanceRadius);

        ThisAITank->AimAt(PlayerTank->GetActorLocation());

        ThisAITank->Fire();
    }
}