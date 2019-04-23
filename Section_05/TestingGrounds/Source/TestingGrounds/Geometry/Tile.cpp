// Chris Nickerson -- TestingGrounds -- Unreal C++ Development


#include "Tile.h"
#include "DrawDebugHelpers.h"
#include "ActorPool.h"
#include "NavigationSystem/Public/NavigationSystem.h"

FSpawnPosition::FSpawnPosition(FVector inPosition /*= FVector::ZeroVector*/, float inYawRotation /*= 0*/, float inRandomizedScaleFactor /*= 1*/)
{
    Location = inPosition;
    YawRotation = inYawRotation;
    RandomizedScaleFactor = inRandomizedScaleFactor;
}

FSpawningAttributes::FSpawningAttributes(int inMinSpawn /*= 0*/, int inMaxSpawn /*= 1*/, float inMinPossibleScaling /*= 1.0f*/, float inMaxPossibleScaling /*= 1.0f*/, float inAcceptableRadius /*= 300.0f*/)
{
    MinSpawn = inMinSpawn;
    MaxSpawn = inMaxSpawn;
    MinPossibleScaling = inMinPossibleScaling;
    MaxPossibleScaling = inMaxPossibleScaling;
    AcceptableRadius = inAcceptableRadius;
}

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

void ATile::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    Super::EndPlay(EndPlayReason);
    if (Pool == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("[%s] EndPlay: Pool is null."), *GetName());
        return;
    }

    if (NavMeshBoundsVolume == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("[%s] EndPlay: NavMeshBoundsVolume is null"), *GetName());
        return;
    }
    Pool->Return(NavMeshBoundsVolume);
}

// Called every frame
void ATile::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

}

void ATile::PlaceActors(TSubclassOf<AActor> ToSpawn, FSpawningAttributes SpawningAttributes)
{
    TArray<FSpawnPosition> SpawnPositions = GetRandomSpawnPositions(SpawningAttributes);

    for (FSpawnPosition SpawnPosition : SpawnPositions)
    {
        PlaceActor(ToSpawn, SpawnPosition);
    }
}

TArray<FSpawnPosition> ATile::GetRandomSpawnPositions(FSpawningAttributes SpawningAttributes)
{
    TArray<FSpawnPosition> SpawnPositions;
    int NumberToSpawn = FMath::RandRange(SpawningAttributes.MinSpawn, SpawningAttributes.MaxSpawn);
    for (size_t i = 0; i < NumberToSpawn; i++)
    {
        FVector SpawnPoint;
        float RandomizedScalingFactor = FMath::RandRange(SpawningAttributes.MinPossibleScaling, SpawningAttributes.MaxPossibleScaling);
        if (FindEmptyLocation(SpawnPoint, SpawningAttributes.AcceptableRadius * RandomizedScalingFactor))
        {
            float RandomRotation = FMath::RandRange(0.0f, 360.0f);
            SpawnPositions.Add(FSpawnPosition(SpawnPoint, RandomRotation, RandomizedScalingFactor));;
        }
    }

    return SpawnPositions;
}

void ATile::SetPool(UActorPool* InPool)
{
    UE_LOG(LogTemp, Warning, TEXT("[%s] SetPool: Setting pool %s "), *GetName(), *(InPool->GetName()));
    Pool = InPool;

    PositionNavMeshBoundsVolume();

}

void ATile::PositionNavMeshBoundsVolume()
{
    if (Pool == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("[%s] PositionNavMeshBoundsVolume: Pool is null."), *GetName());
        return;
    }

    NavMeshBoundsVolume = Pool->Checkout();

    if (NavMeshBoundsVolume == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("[%s] PositionNavMeshBoundsVolume: Not enough actors in pool"), *GetName());
        return;
    }

    UE_LOG(LogTemp, Warning, TEXT("[%s] PositionNavMeshBoundsVolume: Checked out {%s}"), *GetName(), *(NavMeshBoundsVolume->GetName()));

    NavMeshBoundsVolume->SetActorLocation(GetActorLocation() + NavigationBoundsOffset);
    UNavigationSystemV1::GetNavigationSystem(GetWorld())->Build();
}

AActor* ATile::PlaceActor(TSubclassOf<AActor> ActorToSpawn, const FSpawnPosition& SpawnPosition)
{
    AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorToSpawn);
    SpawnedActor->SetActorRelativeLocation(SpawnPosition.Location);
    SpawnedActor->AttachToActor(this, FAttachmentTransformRules(EAttachmentRule::KeepRelative, false));
    SpawnedActor->SetActorRotation(FRotator(0, SpawnPosition.YawRotation, 0));
    SpawnedActor->SetActorScale3D(SpawnedActor->GetActorScale() * SpawnPosition.RandomizedScaleFactor);
    return SpawnedActor;
}


bool ATile::FindEmptyLocation(FVector& SpawnPoint, float Radius)
{
    FBox Bounds(MinExtent, MaxExtent);
    bool bFoundEmptyLocation = false;
    for (size_t i = 0; i < MAX_TRIES_FOR_LOCATION && !bFoundEmptyLocation; ++i)
    {
        SpawnPoint = FMath::RandPointInBox(Bounds);
        if (CanSpawnAtLocation(SpawnPoint, Radius))
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
    /*FColor ResultColor = HasHit ? FColor::Red : FColor::Green;
    DrawDebugCapsule(GetWorld(), GlobalLocation, 0, Radius, FQuat::Identity, ResultColor, true, 100);*/
    return !HasHit;
}



