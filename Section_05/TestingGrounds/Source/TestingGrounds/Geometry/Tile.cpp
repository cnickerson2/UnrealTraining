// Chris Nickerson -- TestingGrounds -- Unreal C++ Development


#include "Tile.h"
#include "DrawDebugHelpers.h"
#include "WorldCollision.h"

// Sets default values
ATile::ATile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
    CastSphere(GetActorLocation(), 300);
	
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn, int MaxSpawn)
{
    FVector Min (0, -2000, 0);
    FVector Max (4000, 2000, 0);
    FBox Bounds (Min, Max);
    int NumberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);
    for(size_t i=0; i < NumberToSpawn; i++)
    {
        FVector SpawnPoint = FMath::RandPointInBox(Bounds);
        SpawnActorAtLocation(SpawnPoint, ToSpawn);
    }
}

AActor* ATile::SpawnActorAtLocation(FVector SpawnPoint, TSubclassOf<AActor> ActorToSpawn)
{
    AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorToSpawn);
    SpawnedActor->SetActorRelativeLocation(SpawnPoint);
    SpawnedActor->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative,false));
    return SpawnedActor;
}

bool ATile::CastSphere(FVector Location, float Radius)
{
    FHitResult HitResult;
    bool HasHit = GetWorld()->SweepSingleByChannel(
        HitResult,
        Location,
        Location,
        FQuat::Identity,
        ECollisionChannel::ECC_GameTraceChannel2,
        FCollisionShape::MakeSphere(Radius)
    );
    FColor ResultColor = HasHit ? FColor::Red : FColor::Green;
    UE_LOG(LogTemp, Warning, TEXT("Has hit? %i. HitResult: %s"), HasHit, *HitResult.ToString());
    DrawDebugSphere(GetWorld(), Location, Radius, 100, ResultColor, true, 100);
    return HasHit;
}
