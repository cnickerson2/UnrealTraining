// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel; // Forward Declaration
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

protected:	
    // Sets default values for this pawn's properties
    ATank();

    virtual void BeginPlay() override;

    double LastFireTime = 0;

    UPROPERTY(EditDefaultsOnly, Category = Firing)
    float ReloadTimeInSeconds = 3.0f;

    UPROPERTY(EditDefaultsOnly, Category = Firing)
    float LaunchSpeed = 4000;

    UPROPERTY(EditDefaultsOnly, Category = Setup)
    TSubclassOf<AProjectile> ProjectileBlueprint; // Alternative is to use TSubclassOf<T>

    UTankBarrel* Barrel = nullptr; // TODO: Remove and put in AimingComponent
    

    

public:


    UFUNCTION(BlueprintCallable, Category = "Actions")
    void Fire();
};
