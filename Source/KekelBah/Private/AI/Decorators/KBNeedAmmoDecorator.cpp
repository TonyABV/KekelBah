// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Decorators/KBNeedAmmoDecorator.h"
#include "AIController.h"
#include "KBUtils.h"
#include "Weapon/KBWeaponComponent.h"
#include "KBBaseWeaponActor.h"

UKBNeedAmmoDecorator::UKBNeedAmmoDecorator()
{
    NodeName = "NeedAmmo";
}

bool UKBNeedAmmoDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    const auto Controller = OwnerComp.GetAIOwner();
    if (!Controller) return false;

    const auto WeaponComponent = KBUtils::GetPlayerComponent<UKBWeaponComponent>(Controller->GetPawn());

    const auto Weapon = WeaponComponent->GetWeapon(WeaponClass);

    return Weapon && !Weapon->IsAmmoFull();
}
