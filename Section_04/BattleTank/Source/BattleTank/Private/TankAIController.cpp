// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"

ATank* ATankAIController::GetAITank() const
{
    auto ThisTank = Cast<ATank>(GetPawn());
    if(!ThisTank)
    {
        UE_LOG(LogTemp, Error, TEXT("There is no tank object attached to %s"), *GetName());
    }
    return ThisTank;
}

ATank* ATankAIController::GetPlayerTank() const
{
    auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

    if(!PlayerPawn)
    {
        UE_LOG(LogTemp, Error, TEXT("There is no pawn attached to the First Player Controller"));
        return nullptr;
    }

    return Cast<ATank>(PlayerPawn);
}

void ATankAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    AimAtPlayer();
}

void ATankAIController::AimAtPlayer()
{
    if(GetAITank() && GetPlayerTank())
    {
        GetAITank()->AimAt(GetPlayerTank()->GetActorLocation());
    }
}

void ATankAIController::BeginPlay()
{
    Super::BeginPlay();

}