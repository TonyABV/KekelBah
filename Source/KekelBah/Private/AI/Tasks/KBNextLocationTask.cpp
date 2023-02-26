// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Tasks/KBNextLocationTask.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"

UKBNextLocationTask::UKBNextLocationTask()
{
    NodeName = "NextLocation";
}

EBTNodeResult::Type UKBNextLocationTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    const auto Controller = OwnerComp.GetAIOwner();
    const auto BlackBoard = OwnerComp.GetBlackboardComponent();

    if (!Controller || !BlackBoard) return EBTNodeResult::Failed;

    const auto Pawn = Controller->GetPawn();

    if (!Pawn) return EBTNodeResult::Failed;

    const auto NavigationSystem = UNavigationSystemV1::GetCurrent(Pawn);

    if (!Pawn) return EBTNodeResult::Failed;

    FVector Location = Pawn->GetActorLocation();

    if (!bSelfCenter)
    {
        AActor* CenterActor = Cast<AActor>(BlackBoard->GetValueAsObject(AimActorKey.SelectedKeyName));
        if (!CenterActor) return EBTNodeResult::Failed;
        Location = CenterActor->GetActorLocation();
    }

    FNavLocation NextLocation;
    const auto Succeed = NavigationSystem->GetRandomReachablePointInRadius(Location, Radius, NextLocation);

    if (!Succeed)  return EBTNodeResult::Failed;

    BlackBoard->SetValueAsVector("NextLocation", NextLocation.Location);

    return EBTNodeResult::Succeeded;
}
