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

    SpawnWeapon();
}

void UKBWeaponComponent::SpawnWeapon()
{
    if (!IsValid(GetWorld())) return;

    FActorSpawnParameters SpawnParameters;
    SpawnParameters.Owner = GetOwner();
    CurrentWeapon = GetWorld()->SpawnActor<AKBBaseWeaponActor>(WeaponClass, SpawnParameters);

    if (!IsValid(CurrentWeapon)) return;

    ACharacter* OwnerChar = Cast<ACharacter>(GetOwner());

    if (!IsValid(OwnerChar)) return;

    FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
    CurrentWeapon->AttachToComponent(OwnerChar->GetMesh(), AttachmentRules, WeaponAttachPointName);

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
