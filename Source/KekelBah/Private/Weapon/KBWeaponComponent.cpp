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

    CurrentWeapon = GetWorld()->SpawnActor<AKBBaseWeaponActor>(WeaponClass);

    if (!IsValid(CurrentWeapon)) return;

    ACharacter* OwnerChar = Cast<ACharacter>(GetOwner());

    if (!IsValid(OwnerChar)) return;

    FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
    CurrentWeapon->AttachToComponent(OwnerChar->GetMesh(), AttachmentRules, WeaponAttachPointName);

}

void UKBWeaponComponent::Fire()
{
    if (!IsValid(CurrentWeapon)) return;
    CurrentWeapon->Fire();
}
