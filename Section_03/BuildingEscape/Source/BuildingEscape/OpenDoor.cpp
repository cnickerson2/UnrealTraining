// Copyright has not been done

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"

#define OUT


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

    if (!PressurePlate)
    {
        UE_LOG(LogTemp,Error,TEXT("Pressure Plate is not assigned on %s"), *(GetOwner()->GetName()))
    }

    // Find Owner
    Owner = GetOwner();
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // Poll the Trigger Volume
   
    if (GetTotalMassOfActorsOnPlate() > TriggerMass) // TODO make into a parameter
    {
        // Open the Door
        OnOpen.Broadcast();
    }
    else
    {
        // Close the Door
        OnClose.Broadcast();
    }
}

float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
    float totalMass = 0.0f;
    
    // Find all the overlapping actors
    TArray<AActor*> overlappyingActors;

    if (!PressurePlate)
    {
        return totalMass;
    }

    PressurePlate->GetOverlappingActors(OUT overlappyingActors);

    // Iterate through them adding their masses
    for (const auto* overlappingActor : overlappyingActors)
    {

        totalMass += overlappingActor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
        UE_LOG(LogTemp, Warning, TEXT("%s on Pressure Plate"), *(overlappingActor->GetName()));
    }

    return totalMass;
}

