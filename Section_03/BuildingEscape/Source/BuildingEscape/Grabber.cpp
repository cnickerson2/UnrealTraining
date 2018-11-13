// Copyright has not been done

#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "CollisionQueryParams.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
    /// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
    /// off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UGrabber::BeginPlay()
{
    Super::BeginPlay();

    FindPhysicsHandleComponent();

    FindInputComponent();

}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    /// If the physics handle is not attached, break out;
    if (!PhysicsHandle)
    {
        return;
    }
    ///if the physics handle is attached
    if (PhysicsHandle->GrabbedComponent)
    {
        /// Move the object that's attached
        PhysicsHandle->SetTargetLocation(UGrabber::GetLineTracePoints().v2);
    }
}

// Get the Starting Point and Ending point of the LineTrace
FTwoVectors UGrabber::GetLineTracePoints() const
{
    FVector StartLocation;
    FRotator PlayerViewPointRotation;

    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT StartLocation, OUT PlayerViewPointRotation);
    FVector EndLocation = StartLocation + PlayerViewPointRotation.Vector() * Reach;
    return FTwoVectors(StartLocation, EndLocation);
}

// Get the first target that is hit by the linetrace
FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
    ///Line Trace outwards until hit or reach met
    FHitResult HitResult;
    /// Setup query parameters
    FCollisionQueryParams TraceParameters = FCollisionQueryParams(FName(TEXT("")), false, GetOwner());
    FTwoVectors TracePoints = UGrabber::GetLineTracePoints();

    GetWorld()->LineTraceSingleByObjectType(
        OUT HitResult, // Sets the results in the HitResult object
        TracePoints.v1, // Starting point
        TracePoints.v2, // End Point
        FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), // Only grab things that have a Physics Body
        TraceParameters
    );

    return HitResult;
}

// Look for attached input component
void UGrabber::FindInputComponent()
{
    InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
    if (InputComponent == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("The Input Component is missing on object %s. Add one to its blueprint"), *(GetOwner()->GetName()));
        return;
            
    }

    /// Bind the input action
    InputComponent->BindAction("Grab", EInputEvent::IE_Pressed, this, &UGrabber::Grab);
    InputComponent->BindAction("Grab", EInputEvent::IE_Released, this, &UGrabber::Release);
}

// Look for attached physics handle
void UGrabber::FindPhysicsHandleComponent()
{
    PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
    if (PhysicsHandle == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("The Physics Handle Component is missing on object %s. Add one to its blueprint"), *(GetOwner()->GetName()));
        return;
    }
}

void UGrabber::Grab()
{
    /// LINE TRACE and reach any actors with physics body
    auto hitResult = GetFirstPhysicsBodyInReach();

    auto ComponentToGrab = hitResult.GetComponent();
    auto ActorHit = hitResult.GetActor();
    /// If we hit something then attach a physics handle
    if (ActorHit)
    {
        PhysicsHandle->GrabComponentAtLocationWithRotation(
            ComponentToGrab, 
            NAME_None, // No Bones since it's static
            ComponentToGrab->GetOwner()->GetActorLocation(), 
            ComponentToGrab->GetOwner()->GetActorRotation()
        );
    }
}

void UGrabber::Release()
{
    PhysicsHandle->ReleaseComponent();
}