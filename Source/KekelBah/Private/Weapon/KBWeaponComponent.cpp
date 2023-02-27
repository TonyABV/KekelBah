// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon/KBWeaponComponent.h"

#include "GameFramework/Character.h"
#include "KBBaseWeaponActor.h"
#include "Animations/KBEquipFinishedAnimNotify.h"
#include "Animations/KBReloadFinishedAnimNotify.h"

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
    InitAnimations();
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

    for (const auto& Data : WeaponData)
    {
        FActorSpawnParameters SpawnParameters;
        SpawnParameters.Owner = OwnerChar;
        AKBBaseWeaponActor* Weapon = GetWorld()->SpawnActor<AKBBaseWeaponActor>(Data.WeaponClass, SpawnParameters);

        if (!IsValid(Weapon)) continue;
        Weapons.Add(Weapon);

        Weapon->OnClipEmpty.AddUObject(this, &UKBWeaponComponent::OnEmptyClip);

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
    if (WeaponIndex < 0 || WeaponIndex >= Weapons.Num())
    {
        UE_LOG(LogTemp, Warning, TEXT("EquipWeapon: Invalid WeaponIndex: %i"), WeaponIndex);
        return;
    }
    
    ACharacter* OwnerChar = Cast<ACharacter>(GetOwner());

    if (!OwnerChar) return;

    if (CurrentWeapon)
    {
        CurrentWeapon->EndFire();
        AttachWeaponToMesh(CurrentWeapon, OwnerChar->GetMesh(), WeaponArmoryPointName);
    }

    CurrentWeapon = Weapons[WeaponIndex];
    AttachWeaponToMesh(CurrentWeapon, OwnerChar->GetMesh(), WeaponEquipPointName);

    PlayAnimMontage(ChangeWeaponAnimation);
    bEquipInProgress = true;

    const auto CurrentWeaponData = WeaponData.FindByPredicate(
        [&](const FWeaponData& Data)  //
        {
            return Data.WeaponClass == CurrentWeapon->GetClass();  //
        });

    CurrentReloadAnim = CurrentWeaponData ? CurrentWeaponData->ReloadAnim : nullptr;
}

void UKBWeaponComponent::PlayAnimMontage(UAnimMontage* AnimMontage)
{
    ACharacter* Owner = GetOwner<ACharacter>();
    if (!IsValid(Owner)) return;
    Owner->PlayAnimMontage(AnimMontage);
}

void UKBWeaponComponent::InitAnimations()
{
    UKBEquipFinishedAnimNotify* EquipFinishedNotify = FindAnimNotifyByClass<UKBEquipFinishedAnimNotify>(ChangeWeaponAnimation);
    if (EquipFinishedNotify)
    {
        EquipFinishedNotify->OnNotified.AddUObject(this, &UKBWeaponComponent::OnEquipFinished);
    }

    for (auto Data : WeaponData)
    {
        UKBReloadFinishedAnimNotify* ReloadFinishedNotify = FindAnimNotifyByClass<UKBReloadFinishedAnimNotify>(Data.ReloadAnim);
        if (ReloadFinishedNotify)
        {
            ReloadFinishedNotify->OnNotified.AddUObject(this, &UKBWeaponComponent::OnReloadFinished);
        }
    }
}

void UKBWeaponComponent::OnEquipFinished(USkeletalMeshComponent* MeshComp)
{
    ACharacter* Char = GetOwner<ACharacter>();
    if (!Char) return;
    if (Char->GetMesh() == MeshComp)
    {
        bEquipInProgress = false;
        UE_LOG(LogTemp, Display, TEXT("Weapon equiped"));
    }
}

bool UKBWeaponComponent::CanReload() const
{
    return CurrentWeapon          //
           && !bEquipInProgress   //
           && !bReloadInProgress  //
           && CurrentWeapon->CanChangeClip();
}

void UKBWeaponComponent::OnEmptyClip(AKBBaseWeaponActor* EmptyWeapon)
{
    if (EmptyWeapon && CurrentWeapon == EmptyWeapon)
    {
        ChangeClip();
    }
    else
    {
        for (auto Weapon : Weapons)
        {
            if (Weapon == EmptyWeapon)
            {
                EmptyWeapon->ChangeClip();
            }
        }
    }
    
}

void UKBWeaponComponent::ChangeClip()
{
    if (!CanReload()) return;

    if (CurrentWeapon) CurrentWeapon->EndFire();
    CurrentWeapon->ChangeClip();
    bReloadInProgress = true;
    PlayAnimMontage(CurrentReloadAnim);
}

void UKBWeaponComponent::OnReloadFinished(USkeletalMeshComponent* MeshComp)
{
    ACharacter* Char = GetOwner<ACharacter>();
    if (!Char) return;
    if (Char->GetMesh() == MeshComp)
    {
        bReloadInProgress = false;
        UE_LOG(LogTemp, Display, TEXT("Weapon reloaded"));
    }
}

bool UKBWeaponComponent::CanFire() const
{
    return CurrentWeapon && !bEquipInProgress && !bReloadInProgress;
}

bool UKBWeaponComponent::CanEquip() const
{
    return !bEquipInProgress && !bReloadInProgress;
}

void UKBWeaponComponent::StartFire()
{
    if (!CanFire()) return;
    CurrentWeapon->StartFire();
}

void UKBWeaponComponent::EndFire()
{
    if (!CurrentWeapon) return;
    CurrentWeapon->EndFire();
}

void UKBWeaponComponent::NextWeapon()
{
    if (!CanEquip()) return;

    CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
    EquipWeapon(CurrentWeaponIndex);
}

void UKBWeaponComponent::Reload()
{
    ChangeClip();
}

bool UKBWeaponComponent::GetUIWeaponData(FUIWeaponData& UIWeaponData) const
{
    if (!CurrentWeapon) return false;

    UIWeaponData = CurrentWeapon->GetUIWeaponData();

    return true;
}

bool UKBWeaponComponent::GetCurrentAmmoData(FWeaponAmmo& WeaponAmmo) const
{
    if (!CurrentWeapon) return false;

    WeaponAmmo = CurrentWeapon->GetCurrentAmmoData();

    return true;
}

bool UKBWeaponComponent::TryAddAmmo(TSubclassOf<AKBBaseWeaponActor> WeaponType, int32 ClipAmount)
{
    auto Weapon = GetWeapon(WeaponType);

    if (Weapon)
    {
        return Weapon->TryAddAmmo(ClipAmount);
    }
    return false;
}

AKBBaseWeaponActor* UKBWeaponComponent::GetWeapon(TSubclassOf<AKBBaseWeaponActor> WeaponClass)
{
    for (auto Weapon : Weapons)
    {
        if (Weapon && Weapon->IsA(WeaponClass))
        {
            return Weapon;
        }
    }
    return nullptr;
}
