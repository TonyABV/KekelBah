// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/KBFireService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "KBUtils.h"
#include "Weapon/KBWeaponComponent.h"

UKBFireService::UKBFireService()
{
    NodeName = "Fire";
}

void UKBFireService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    const auto Controller = OwnerComp.GetAIOwner();
    const auto Blackboard = OwnerComp.GetBlackboardComponent();

    const auto HasAim = Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);

    if (Controller)
    {
        const auto WeaponComponent = KBUtils::GetPlayerComponent<UKBWeaponComponent>(Controller->GetPawn());
        if (WeaponComponent)
        {
            HasAim ? WeaponComponent->StartFire() : WeaponComponent->EndFire();
        }
    }

    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
