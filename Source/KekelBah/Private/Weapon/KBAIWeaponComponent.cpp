// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/KBAIWeaponComponent.h"
#include "KBBaseWeaponActor.h"

void UKBAIWeaponComponent::StartFire()
{
    if (!CanFire()) return;

    if(CurrentWeapon->IsAmmoEmpty())
    {
        NextWeapon();
    }
    else
    {
        CurrentWeapon->StartFire();
    }
}

void UKBAIWeaponComponent::NextWeapon()
{
    if (!CanEquip()) return;

    int32 NextWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();

    while (NextWeaponIndex != CurrentWeaponIndex)
    {
        if (!Weapons[NextWeaponIndex]->IsAmmoEmpty()) break;

        NextWeaponIndex = (NextWeaponIndex + 1) % Weapons.Num();
    }

    if (NextWeaponIndex != CurrentWeaponIndex)
    {
        CurrentWeaponIndex = NextWeaponIndex;
        EquipWeapon(NextWeaponIndex);
    }
}
