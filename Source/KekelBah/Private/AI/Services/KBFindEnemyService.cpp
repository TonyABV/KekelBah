// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/KBFindEnemyService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "KBUtils.h"
#include "AI/KBAIPerceptionComponent.h"

UKBFindEnemyService::UKBFindEnemyService()
{
    NodeName = "FindEnemy";
}

void UKBFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    auto Blackboard = OwnerComp.GetBlackboardComponent();

    if (Blackboard)
    {
        const auto AIController = OwnerComp.GetAIOwner();
        const auto PerceptionComponent = KBUtils::GetPlayerComponent<UKBAIPerceptionComponent>(AIController);
        if (PerceptionComponent)
        {
            Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClosestEnemy());
        }
    }

    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
