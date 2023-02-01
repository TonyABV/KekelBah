// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/KBAmmoPickup.h"

DEFINE_LOG_CATEGORY_STATIC(LogAmmoPickup, All, All)

bool AKBAmmoPickup::GivePickupTo(APawn* Pawn)
{
    UE_LOG(LogAmmoPickup, Display, TEXT("AmmoPickup was taken"))
    return true;
}
