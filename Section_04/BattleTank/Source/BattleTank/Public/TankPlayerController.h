// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
    GENERATED_BODY()

private:
    UPROPERTY(EditAnywhere)
    float CrosshairXLocation = 0.5f;
    UPROPERTY(EditAnywhere)
    float CrosshairYLocation = 0.333333f;
    UPROPERTY(EditAnywhere)
    float LineTraceRange = 100000.0f;

    
	
    
public:


    virtual void BeginPlay() override;

    

    virtual void Tick(float DeltaSeconds) override;
private:

    // Start the tank moving the barrel so that a shot would hit where the crosshair intersects the world
    void AimTowardsCrosshair();
    
    ATank* GetControlledTank() const;
    bool GetSightRayHitLocation(FVector& OutHitLocation) const;

    bool GetLookDirection(const FVector2D& ScreenLocation, FVector& LookDirection) const;
    bool GetLookVectorHitLocation(const FVector& LookDirection, FVector& HitLocation) const;
};
