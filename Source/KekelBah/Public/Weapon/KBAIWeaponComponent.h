// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/KBWeaponComponent.h"
#include "KBAIWeaponComponent.generated.h"

/**
 * 
 */
UCLASS()
class KEKELBAH_API UKBAIWeaponComponent : public UKBWeaponComponent
{
	GENERATED_BODY()

public:

	virtual void StartFire() override;

	virtual void NextWeapon() override;
};
