// Chris Nickerson -- TestingGrounds -- Unreal C++ Development

#pragma once

#include "CoreMinimal.h"
#include "Components/HierarchicalInstancedStaticMeshComponent.h"
#include "GrassComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TESTINGGROUNDS_API UGrassComponent : public UHierarchicalInstancedStaticMeshComponent
{
	GENERATED_BODY()

public:	

    UPROPERTY(EditDefaultsOnly, Category = "Spawning")
    FBox SpawningExtents = FBox(FVector(0,-2000,0),FVector(4000,2000,0));
    UPROPERTY(EditDefaultsOnly, Category = "Spawning")
    int SpawnCount = 3000;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
    void SpawnGrass();
		
};
