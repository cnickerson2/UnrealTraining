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

	/// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

    FindPhysicsHandleComponent();

    FindInputComponent();
	
}

// Look for attached input component
void UGrabber::FindInputComponent()
{
    InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
    if (PhysicsHandle)
    {
        UE_LOG(LogTemp, Warning, TEXT("The Input Component was found on %s"), *(GetOwner()->GetName()))

            /// Bind the input action
            InputComponent->BindAction("Grab", EInputEvent::IE_Pressed, this, &UGrabber::Grab);
        InputComponent->BindAction("Grab", EInputEvent::IE_Released, this, &UGrabber::ReleaseGrab);
    }
    else
    {
        UE_LOG(LogTemp, Error, TEXT("The Input Component is missing on object %s. Add one to its blueprint"), *(GetOwner()->GetName()))
    }
}

// Look for attached physics handle
void UGrabber::FindPhysicsHandleComponent()
{        
        PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
        if (PhysicsHandle)
        {
            // Physics Handle was found
        }
        else
        {
            UE_LOG(LogTemp, Error, TEXT("The Physics Handle Component is missing on object %s. Add one to its blueprint"), *(GetOwner()->GetName()))
        }
    
}



void UGrabber::Grab()
{
    UE_LOG(LogTemp, Warning, TEXT("Grab was Pressed"));

    /// LINE TRACE and reach any actors with physics body
    auto hitResult = GetFirstPhysicsBodyInReach();

    auto ComponentToGrab = hitResult.GetComponent();
    auto ActorHit = hitResult.GetActor();
    /// If we hit something then attach a physics handle
    if(ActorHit)
    {
        PhysicsHandle->GrabComponentAtLocationWithRotation(ComponentToGrab, NAME_None, ComponentToGrab->GetOwner()->GetActorLocation(), ComponentToGrab->GetOwner()->GetActorRotation());
    }
}

void UGrabber::ReleaseGrab()
{
    UE_LOG(LogTemp, Warning, TEXT("Grab was Released"));

    // TODO release physics handle
    PhysicsHandle->ReleaseComponent();
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    ///if the physics handle is attached
    if (PhysicsHandle->GrabbedComponent)
    {
        /// Get the player viewpoint this tick
        FVector PlayerViewpointLocation;
        FRotator PlayerViewpointRotation;
        GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewpointLocation, OUT PlayerViewpointRotation);


        /// Draw a red trace in the world to visualize

        FVector LineTraceEnd = PlayerViewpointLocation + (PlayerViewpointRotation.Vector() * Reach);
        /// Move the object that's attached
        PhysicsHandle->SetTargetLocation(LineTraceEnd);
    }
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach() const
{
    /// Get the player viewpoint this tick
    FVector PlayerViewpointLocation;
    FRotator PlayerViewpointRotation;
    GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT PlayerViewpointLocation, OUT PlayerViewpointRotation);


    /// Draw a red trace in the world to visualize

    FVector LineTraceEnd = PlayerViewpointLocation + (PlayerViewpointRotation.Vector() * Reach);
    DrawDebugLine(GetWorld(), PlayerViewpointLocation, LineTraceEnd, FColor(255, 0, 0), false, 0.0f, 0.0f, 10.0f);


    /// Setup query parameters
    FCollisionQueryParams TraceParameters = FCollisionQueryParams(FName(TEXT("")), false, GetOwner());

    /// Line trace within the world to reach distance
    FHitResult LineTraceHit;

    bool wasHit = GetWorld()->LineTraceSingleByObjectType(OUT LineTraceHit, PlayerViewpointLocation, LineTraceEnd, FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), TraceParameters);
    if (wasHit)
    {

        UE_LOG(LogTemp, Warning, TEXT("Line Trace Hit: %s"), *LineTraceHit.GetActor()->GetName())
    }
    
    return LineTraceHit;
}
