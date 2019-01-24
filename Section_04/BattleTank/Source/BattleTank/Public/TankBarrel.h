// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

// Holds Barrel's Properties and Elevate Methods
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent), hideCategories = (Collision))
class BATTLETANK_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()

public:

    void Elevate(float DegreesPerSecond);

private:

    UPROPERTY(EditAnywhere, Category = Setup)
        float MaxDegreesPerSecond = 20.0f; 
    UPROPERTY(EditAnywhere, Category = Setup)
        float MinElevationInDegress = 0.0f; 
    UPROPERTY(EditAnywhere, Category = Setup)
        float MaxElevationInDegrees = 40.0f;
};
