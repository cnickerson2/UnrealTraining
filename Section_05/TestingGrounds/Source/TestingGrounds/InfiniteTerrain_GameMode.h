// Chris Nickerson -- TestingGrounds -- Unreal C++ Development

#pragma once

#include "CoreMinimal.h"
#include "TestingGroundsGameMode.h"
#include "InfiniteTerrain_GameMode.generated.h"

class ANavMeshBoundsVolume;
class UActorPool;
/**
 * 
 */
UCLASS()
class TESTINGGROUNDS_API AInfiniteTerrain_GameMode : public ATestingGroundsGameMode
{
	GENERATED_BODY()
	
public:

    AInfiniteTerrain_GameMode();

    UFUNCTION(BlueprintCallable, Category = "Bounds Pool")
    void PopulateBoundsVolumePool();


private:
    void AddToPool(ANavMeshBoundsVolume *VolumeToAdd);

protected:    
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Pool")
    UActorPool* NavMeshBoundsVolumePool = nullptr;
};
