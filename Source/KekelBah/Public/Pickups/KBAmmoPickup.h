// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickups/KBBasePickup.h"
#include "KBAmmoPickup.generated.h"


class AKBBaseWeaponActor;

UCLASS()
class KEKELBAH_API AKBAmmoPickup : public AKBBasePickup
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
    TSubclassOf<AKBBaseWeaponActor> WeaponType;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1.0", ClampMax = "10.0"))
    int32 ClipAmount = 10;

private:
    virtual bool GivePickupTo(APawn* Pawn) override;
};
