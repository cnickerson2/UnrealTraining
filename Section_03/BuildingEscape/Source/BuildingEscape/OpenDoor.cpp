// Copyright has not been done

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "Engine/World.h"


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

    // Set the Player whose marked as FirstPlayer to be the one who opens the door
    ActorThatOpensDoor = GetWorld()->GetFirstPlayerController()->GetPawn();

    // Find Owner
    Owner = GetOwner();
}

void UOpenDoor::OpenDoor()
{
    // Create a Rotator
    FRotator NewRotation = FRotator(0, OpenAngle, 0);
    // Set the Rotation
    Owner->SetActorRotation(NewRotation);
}

void UOpenDoor::CloseDoor()
{
    // Create a Rotator
    FRotator NewRotation = FRotator(0, 0, 0);
    // Set the Rotation
    Owner->SetActorRotation(NewRotation);
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    // Poll the Trigger Volume
    // If the ActorThatOpensDoor is in the Volume
    if (PressurePlate && PressurePlate->IsOverlappingActor(ActorThatOpensDoor))
    {
        // Open the Door
        OpenDoor();
        LastDoorOpenTime = GetWorld()->GetTimeSeconds();
    }
    
    // Check if it's time to close the door
    if (LastDoorOpenTime + DoorCloseDelay < GetWorld()->GetTimeSeconds()) 
    {
        CloseDoor();
    }
}

