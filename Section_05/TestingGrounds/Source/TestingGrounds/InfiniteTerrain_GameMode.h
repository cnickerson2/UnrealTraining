// Chris Nickerson -- TestingGrounds -- Unreal C++ Development

#pragma once

#include "CoreMinimal.h"
#include "TestingGroundsGameMode.h"
#include "InfiniteTerrain_GameMode.generated.h"

class ANavMeshBoundsVolume;
/**
 * 
 */
UCLASS()
class TESTINGGROUNDS_API AInfiniteTerrain_GameMode : public ATestingGroundsGameMode
{
	GENERATED_BODY()
	
public:

    UFUNCTION(BlueprintCallable, Category = "Bounds Pool")
    void PopulateBoundsVolumePool();

private:
    void AddToPool(ANavMeshBoundsVolume *VolumeToAdd);
};
