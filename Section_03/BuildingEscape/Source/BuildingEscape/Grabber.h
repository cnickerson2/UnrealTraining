// Copyright has not been done

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/InputComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
    GENERATED_BODY()

private:
    // How far ahead of the the object should it reach
    UPROPERTY(EditAnywhere)
    float Reach = 100.0f;

    UPhysicsHandleComponent* PhysicsHandle = nullptr;

    UInputComponent* InputComponent = nullptr;


    void Grab();
    void Release();

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

    // Look for attached input component
    void FindInputComponent();

    // Look for attached physics handle
    void FindPhysicsHandleComponent();

    // Get the first target that is hit by the linetrace
    FHitResult GetFirstPhysicsBodyInReach() const;

    // Look for attached input component
    FTwoVectors GetLineTracePoints() const;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
