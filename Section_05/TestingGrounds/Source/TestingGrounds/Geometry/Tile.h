// Chris Nickerson -- TestingGrounds -- Unreal C++ Development

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

USTRUCT()
struct FSpawnPosition
{
    GENERATED_USTRUCT_BODY()

        
    FVector Location; 
    float YawRotation; 
    float RandomizedScaleFactor;

    FSpawnPosition(FVector Position = FVector::ZeroVector, float YawRotation = 0, float RandomizedScaleFactor = 1);
};

USTRUCT(BlueprintType)
struct FSpawningAttributes
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
    int MinSpawn;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
    int MaxSpawn; 
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
    float MinPossibleScaling;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
    float MaxPossibleScaling;
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
    float AcceptableRadius;

    FSpawningAttributes(int MinSpawn = 0, int MaxSpawn = 1, float MinPossibleScaling = 1.0f, float MaxPossibleScaling = 1.0f, float AcceptableRadius = 300.0f);
};

class UActorPool;

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

    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

    UFUNCTION(BlueprintCallable, Category = "Spawning")
    void PlaceActors(TSubclassOf<AActor> ToSpawn, FSpawningAttributes SpawningAttributes);

    TArray<FSpawnPosition> GetRandomSpawnPositions(FSpawningAttributes SpawningAttributes);

    UFUNCTION(BlueprintCallable, Category = "Pool")
    void SetPool(UActorPool* Pool);


private:
    
    AActor* PlaceActor(TSubclassOf<AActor> ActorToSpawn, const FSpawnPosition& SpawnPosition);
    
    bool FindEmptyLocation(FVector& SpawnPoint, float Radius);

    bool CanSpawnAtLocation(FVector const & Location, float Radius);

    void PositionNavMeshBoundsVolume();
private:

    const int MAX_TRIES_FOR_LOCATION = 100;

    UActorPool* Pool = nullptr;

    AActor* NavMeshBoundsVolume = nullptr;

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    FVector MinExtent = FVector(0, -2000, 0);

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    FVector MaxExtent = FVector(4000, 2000, 0);

    UPROPERTY(EditDefaultsOnly, Category = "Setup")
    FVector NavigationBoundsOffset = FVector(2000, 0, 0);
};
