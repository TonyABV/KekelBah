// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/KBHealthPickup.h"
#include "KBUtils.h"
#include "Player/Components/KBHealthComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthPickup, All, All)

bool AKBHealthPickup::GivePickupTo(APawn* Pawn)
{
    UKBHealthComponent* HealthComponent = KBUtils::GetPlayerComponent<UKBHealthComponent>(Pawn);
    if (!HealthComponent || HealthComponent->IsDeath()) return false;

    return HealthComponent->TryAddHealth(HealthAmount);
}
