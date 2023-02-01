// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/KBBasePickup.h"
#include "KBHealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class KEKELBAH_API AKBHealthPickup : public AKBBasePickup
{
	GENERATED_BODY()

private:
    virtual bool GivePickupTo(APawn* Pawn) override;
};
