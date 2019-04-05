// Chris Nickerson -- TestingGrounds -- Unreal C++ Development

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PatrolRoute.generated.h"


/*
*   A "Route Card" to help AI choose their next waypoint
*/
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTINGGROUNDS_API UPatrolRoute : public UActorComponent
{
	GENERATED_BODY()

private:		
    UPROPERTY(EditInstanceOnly, Category = "Patrol Route")
    TArray<AActor*> PatrolPoints;

public:
    TArray<AActor*> GetPatrolPoints() const;
		
};
