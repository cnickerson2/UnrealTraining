// Chris Nickerson -- TestingGrounds -- Unreal C++ Development


#include "GrassComponent.h"


// Called when the game starts
void UGrassComponent::BeginPlay()
{
	Super::BeginPlay();

    SpawnGrass();
	
}


void UGrassComponent::SpawnGrass()
{
    for(size_t i = 0; i < SpawnCount; ++i)
    {
        FVector Location = FMath::RandPointInBox(SpawningExtents);
        AddInstance(FTransform(Location));
    }
}

