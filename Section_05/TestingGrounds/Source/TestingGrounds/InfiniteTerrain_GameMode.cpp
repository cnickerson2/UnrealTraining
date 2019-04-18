// Chris Nickerson -- TestingGrounds -- Unreal C++ Development


#include "InfiniteTerrain_GameMode.h"
#include "NavMesh/NavMeshBoundsVolume.h"
#include "EngineUtils.h"

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
    UE_LOG(LogTemp, Warning, TEXT("Volume To Add: %s"), *VolumeToAdd->GetName());
}
