// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/KBAmmoPickup.h"
#include "KBUtils.h"
#include "Weapon/KBWeaponComponent.h"
#include "Components/KBHealthComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogAmmoPickup, All, All)

void AKBAmmoPickup::BeginPlay()
{
    Super::BeginPlay();

    check(WeaponType)
}

bool AKBAmmoPickup::GivePickupTo(APawn* Pawn)
{
    UKBHealthComponent* HealthComponent = KBUtils::GetPlayerComponent<UKBHealthComponent>(Pawn);
    if (!HealthComponent || HealthComponent->IsDeath()) return false;

    UKBWeaponComponent* WeaponComponent = KBUtils::GetPlayerComponent<UKBWeaponComponent>(Pawn);
    if (WeaponComponent && WeaponType)
    {
        return WeaponComponent->TryAddAmmo(WeaponType, ClipAmount);    
    }
    

    UE_LOG(LogAmmoPickup, Display, TEXT("AmmoPickup was taken"))
    return true;
}
