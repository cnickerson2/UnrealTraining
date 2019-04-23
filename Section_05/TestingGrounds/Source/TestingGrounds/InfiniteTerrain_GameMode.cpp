// Chris Nickerson -- TestingGrounds -- Unreal C++ Development


#include "InfiniteTerrain_GameMode.h"
#include "NavMesh/NavMeshBoundsVolume.h"
#include "EngineUtils.h"
#include "ActorPool.h"

AInfiniteTerrain_GameMode::AInfiniteTerrain_GameMode()
{
    NavMeshBoundsVolumePool = CreateDefaultSubobject<UActorPool>(TEXT("Nav Mesh Bounds Volume Pool"));
}

void AInfiniteTerrain_GameMode::PopulateBoundsVolumePool()
{
    auto NavMeshVolumeIterator = TActorIterator<ANavMeshBoundsVolume>(GetWorld());

    while (NavMeshVolumeIterator)
    {
        AddToPool(*NavMeshVolumeIterator);
        
        ++NavMeshVolumeIterator;
    }

    
}


void AInfiniteTerrain_GameMode::AddToPool(ANavMeshBoundsVolume *VolumeToAdd)
{
    NavMeshBoundsVolumePool->Add(VolumeToAdd);
}
