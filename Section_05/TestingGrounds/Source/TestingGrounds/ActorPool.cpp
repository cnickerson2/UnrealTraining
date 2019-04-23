// Chris Nickerson -- TestingGrounds -- Unreal C++ Development


#include "ActorPool.h"

// Sets default values for this component's properties
UActorPool::UActorPool()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

/*
Remove the Actor at the top of the pool stack
*/
AActor* UActorPool::Checkout()
{    
    if(Pool.Num() == 0)
    {
        return nullptr;
    }

    return Pool.Pop();
}

void UActorPool::Return(AActor* ActorToReturn)
{
    Add(ActorToReturn);
}

void UActorPool::Add(AActor* ActorToAdd)
{
    if (ActorToAdd == nullptr)
    {
        UE_LOG(LogTemp, Error, TEXT("[%s] Add: Added null actor."), *GetName());
        return;
    }

    Pool.Push(ActorToAdd);
}

