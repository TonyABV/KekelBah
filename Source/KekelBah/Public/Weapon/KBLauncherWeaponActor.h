// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/KBBaseWeaponActor.h"
#include "KBLauncherWeaponActor.generated.h"

class AKBProjectileBase;

UCLASS()
class KEKELBAH_API AKBLauncherWeaponActor : public AKBBaseWeaponActor
{
	GENERATED_BODY()

public:
	
	virtual void StartFire() override;
	
protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    TSubclassOf<AKBProjectileBase> ProjectileClass;

protected:

	virtual void MakeShot() override;
	
};
