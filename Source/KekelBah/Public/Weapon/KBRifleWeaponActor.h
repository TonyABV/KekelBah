// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/KBBaseWeaponActor.h"
#include "KBRifleWeaponActor.generated.h"

/**
 * 
 */
UCLASS()
class KEKELBAH_API AKBRifleWeaponActor : public AKBBaseWeaponActor
{
	GENERATED_BODY()

public:

    virtual void StartFire() override;
    virtual void EndFire() override;

protected:

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Fire")
    float TimeBetweenShots = 0.2f;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Fire")
    float FireSpreadAngle = 3.f;

    FTimerHandle FireHandle;

protected:

    virtual void MakeShot() override;

    virtual  void GetStartEndPoints(FVector& StartPoint, FVector& EndPoint) override;

};
