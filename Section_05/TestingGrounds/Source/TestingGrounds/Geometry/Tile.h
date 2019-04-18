// Chris Nickerson -- TestingGrounds -- Unreal C++ Development

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UCLASS()
class TESTINGGROUNDS_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable, Category = "Spawning")
        void PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn = 0, int MaxSpawn = 1, float MaxPossibleScaling = 1.0f, float AcceptableRadius = 300.0f);
private:
    
    AActor* PlaceActor(TSubclassOf<AActor> ActorToSpawn, FVector SpawnPointLocation, float YawRotation, float RandomizedScaleFactor);
    
    bool FindEmptyLocation(FVector& SpawnPoint, float Radius);

    bool CanSpawnAtLocation(FVector const & Location, float Radius);
private:

    const int MAX_TRIES_FOR_LOCATION = 100;
};
