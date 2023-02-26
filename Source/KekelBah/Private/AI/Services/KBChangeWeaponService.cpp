// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/Services/KBChangeWeaponService.h"

#include "AIController.h"
#include "KBAIWeaponComponent.h"
#include "KBUtils.h"

UKBChangeWeaponService::UKBChangeWeaponService()
{
    NodeName = "ChangeWeapon";
}

void UKBChangeWeaponService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
    float RandomNumber = FMath::FRand();
    
    if (Probability != 0.f && RandomNumber <= Probability)
    {
        const auto AIController = OwnerComp.GetAIOwner();

        if (AIController && AIController->GetPawn())
        {
            const auto WeaponComponent = KBUtils::GetPlayerComponent<UKBAIWeaponComponent>(AIController->GetPawn());

            if (WeaponComponent)
            {
                WeaponComponent->NextWeapon();
            }
        }
    }

    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
