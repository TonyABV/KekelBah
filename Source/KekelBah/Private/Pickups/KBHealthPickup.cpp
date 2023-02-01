// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/KBHealthPickup.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthPickup, All, All)

bool AKBHealthPickup::GivePickupTo(APawn* Pawn)
{
    UE_LOG(LogHealthPickup, Display, TEXT("HealthPickup was taken"))
    return true;
}
