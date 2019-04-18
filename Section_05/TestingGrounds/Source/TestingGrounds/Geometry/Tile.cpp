// Chris Nickerson -- TestingGrounds -- Unreal C++ Development


#include "Tile.h"
#include "DrawDebugHelpers.h"

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
	
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, int MinSpawn/*=0*/, int MaxSpawn/*=1*/, float MaxPossibleScaling/*= 1.0f*/, float AcceptableRadius /*= 300.0f*/)
{
    int NumberToSpawn = FMath::RandRange(MinSpawn, MaxSpawn);
    for (size_t i = 0; i < NumberToSpawn; i++)
    {
        FVector SpawnPoint;
        float RandomizedScalingFactor = FMath::RandRange(1.0f, MaxPossibleScaling);
        if(FindEmptyLocation(SpawnPoint, AcceptableRadius * RandomizedScalingFactor))
        {
            float RandomRotation = FMath::RandRange(0.0f, 360.0f);
            PlaceActor(ToSpawn, SpawnPoint, RandomRotation, RandomizedScalingFactor);
        }
    }
}

AActor* ATile::PlaceActor(TSubclassOf<AActor> ActorToSpawn, FVector SpawnPointLocation, float YawRotation, float RandomizedScaleFactor)
{
    AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorToSpawn);
    SpawnedActor->SetActorRelativeLocation(SpawnPointLocation);
    SpawnedActor->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative,false));
    SpawnedActor->SetActorRotation(FRotator(0, YawRotation, 0));
    SpawnedActor->SetActorScale3D(SpawnedActor->GetActorScale() * RandomizedScaleFactor);
    return SpawnedActor;
}


bool ATile::FindEmptyLocation(FVector& SpawnPoint, float Radius)
{
    FVector Min(0, -2000, 0);
    FVector Max(4000, 2000, 0);
    FBox Bounds(Min, Max);
    bool bFoundEmptyLocation = false;
    for(size_t i = 0; i < MAX_TRIES_FOR_LOCATION && !bFoundEmptyLocation; ++i)
    {
        SpawnPoint = FMath::RandPointInBox(Bounds);
        if(CanSpawnAtLocation(SpawnPoint,Radius))
        {
            bFoundEmptyLocation = true;
        }
    }
    return bFoundEmptyLocation;
}

bool ATile::CanSpawnAtLocation(FVector const & LocalPosition, float Radius)
{
    FHitResult HitResult;
    FVector GlobalLocation = ActorToWorld().TransformPosition(LocalPosition);
    bool HasHit = GetWorld()->SweepSingleByChannel(
        HitResult,
        GlobalLocation,
        GlobalLocation + 0.0001f,
        FQuat::Identity,
        ECollisionChannel::ECC_GameTraceChannel2,
        FCollisionShape::MakeSphere(Radius)
    );
    FColor ResultColor = HasHit ? FColor::Red : FColor::Green;
    DrawDebugCapsule(GetWorld(), GlobalLocation, 0, Radius, FQuat::Identity, ResultColor, true, 100);
    return !HasHit;
}
