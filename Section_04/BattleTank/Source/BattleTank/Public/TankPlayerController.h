// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class ATank;
class UTankAimingComponent;
/**
 * Responsible for helping the player aim
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
    GENERATED_BODY()

private:
    UPROPERTY(EditDefaultsOnly)
    float CrosshairXLocation = 0.5f;
    UPROPERTY(EditDefaultsOnly)
    float CrosshairYLocation = 0.333333f;
    UPROPERTY(EditDefaultsOnly)
    float LineTraceRange = 100000.0f;

    
	
    
public:


    virtual void BeginPlay() override;

    

    virtual void Tick(float DeltaSeconds) override;
private:

    // Start the tank moving the barrel so that a shot would hit where the crosshair intersects the world
    void AimTowardsCrosshair();

    bool GetSightRayHitLocation(FVector& OutHitLocation) const;

    bool GetLookDirection(const FVector2D& ScreenLocation, FVector& LookDirection) const;
    bool GetLookVectorHitLocation(const FVector& LookDirection, FVector& HitLocation) const;

protected:
    UFUNCTION(BlueprintCallable, Category = "Setup")
    ATank* GetControlledTank() const;

    UFUNCTION(BlueprintImplementableEvent, Category = "Setup")
    void FoundAimingComponent(UTankAimingComponent* AimCompRef);
};
