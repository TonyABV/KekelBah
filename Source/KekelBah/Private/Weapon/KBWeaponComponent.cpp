// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon/KBWeaponComponent.h"

#include "GameFramework/Character.h"
#include "KBBaseWeaponActor.h"

UKBWeaponComponent::UKBWeaponComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UKBWeaponComponent::BeginPlay()
{
    Super::BeginPlay();

    CurrentWeaponIndex = 0;
    SpawnWeapons();
    EquipWeapon(CurrentWeaponIndex);
}

void UKBWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    for (auto Weapon : Weapons)
    {
        Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
        Weapon->Destroy();
    }
    Weapons.Empty();

    Super::EndPlay(EndPlayReason);
}

void UKBWeaponComponent::SpawnWeapons()
{
    ACharacter* OwnerChar = Cast<ACharacter>(GetOwner());

    if (!IsValid(GetWorld()) || !OwnerChar) return;

    for (const auto& WeaponClass : WeaponClasses)
    {
        FActorSpawnParameters SpawnParameters;
        SpawnParameters.Owner = OwnerChar;
        AKBBaseWeaponActor* Weapon = 
            GetWorld()->SpawnActor<AKBBaseWeaponActor>(WeaponClass, SpawnParameters);

        if (!IsValid(Weapon)) continue;
        Weapons.Add(Weapon);

        AttachWeaponToMesh(Weapon, OwnerChar->GetMesh(), WeaponArmoryPointName);
    }
}

void UKBWeaponComponent::AttachWeaponToMesh(AKBBaseWeaponActor* Weapon, USkeletalMeshComponent* SkeletalMesh, const FName& SocketName)
{
    if (!Weapon || !SkeletalMesh) return;

    FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
    Weapon->AttachToComponent(SkeletalMesh, AttachmentRules, SocketName);
}

void UKBWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
    ACharacter* OwnerChar = Cast<ACharacter>(GetOwner());

    if (!OwnerChar) return;

    if (CurrentWeapon)
    {
        CurrentWeapon->EndFire();
        AttachWeaponToMesh(CurrentWeapon, OwnerChar->GetMesh(), WeaponArmoryPointName);
    }

    CurrentWeapon = Weapons[WeaponIndex];
    AttachWeaponToMesh(CurrentWeapon, OwnerChar->GetMesh(), WeaponEquipPointName);
}

void UKBWeaponComponent::StartFire()
{
    if (!IsValid(CurrentWeapon)) return;
    CurrentWeapon->StartFire();
}

void UKBWeaponComponent::EndFire()
{
    if (!IsValid(CurrentWeapon)) return;
    CurrentWeapon->EndFire();
}

void UKBWeaponComponent::NextWeapon()
{
    CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
    EquipWeapon(CurrentWeaponIndex);
}
