// Chris Nickerson -- TestingGrounds -- Unreal C++ Development

#include "PatrolRoute.h"



TArray<AActor*> UPatrolRoute::GetPatrolPoints() const
{
    return PatrolPoints;
}
