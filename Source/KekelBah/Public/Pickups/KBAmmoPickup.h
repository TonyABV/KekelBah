// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/KBBasePickup.h"
#include "KBAmmoPickup.generated.h"

/**
 * 
 */
UCLASS()
class KEKELBAH_API AKBAmmoPickup : public AKBBasePickup
{
	GENERATED_BODY()

private:
    virtual bool GivePickupTo(APawn* Pawn) override;
};
