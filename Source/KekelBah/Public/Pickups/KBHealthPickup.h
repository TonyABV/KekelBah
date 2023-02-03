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
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "0.0", ClampMax = "100.0"))
    float HealthAmount = 50.f;

private:
    virtual bool GivePickupTo(APawn* Pawn) override;
};
