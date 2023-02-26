// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorators/KBHealthPercentDecorator.h"

#include "AIController.h"
#include "KBUtils.h"
#include "KBHealthComponent.h"


UKBHealthPercentDecorator::UKBHealthPercentDecorator()
{
    NodeName = "HealthPercent";
}

bool UKBHealthPercentDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    const auto Controller = OwnerComp.GetAIOwner();
    if (!Controller) return false;

    const auto HealthComponent = KBUtils::GetPlayerComponent<UKBHealthComponent>(Controller->GetPawn());

    if (!HealthComponent || HealthComponent->IsDeath()) return false;

    return HealthComponent->GetHealthPercent() < HealthPercent;
}
