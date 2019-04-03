// Fill out your copyright notice in the Description page of Project Settings.

#include "ChooseNextWaypoint.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PatrolRoute.h"

EBTNodeResult::Type UChooseNextWaypoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory); 

    
    // Get The Patrol Points
    auto ControlledPawn = OwnerComp.GetAIOwner()->GetPawn();
    auto PatrolRoute = ControlledPawn->FindComponentByClass<UPatrolRoute>();
    if(!ensure(PatrolRoute)) // Protect against no patrol route component
    {
        return EBTNodeResult::Failed;
    }

    auto PatrolPoints = PatrolRoute->GetPatrolPoints();
    if(PatrolPoints.Num() == 0) // Protect against empty patrol routes
    {
        UE_LOG(LogTemp, Warning, TEXT("%s is missing Patrol Points"), *ControlledPawn->GetName());
        return EBTNodeResult::Failed;
    }


    // Set the Next Waypoint
    auto BlackboardComp = OwnerComp.GetBlackboardComponent();
    auto Index = BlackboardComp->GetValueAsInt(IndexKey.SelectedKeyName);
    BlackboardComp->SetValueAsObject(WaypointKey.SelectedKeyName, PatrolPoints[Index]);

    // Cycle the Index

    auto NextIndex = (Index + 1) % PatrolPoints.Num();
    BlackboardComp->SetValueAsInt(IndexKey.SelectedKeyName, NextIndex);



    return EBTNodeResult::Succeeded;
}
