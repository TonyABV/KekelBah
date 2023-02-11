// Fill out your copyright notice in the Description page of Project Settings.


#include "KBPlayerHUDWidget.h"
#include "Player/Components/KBHealthComponent.h"
#include "Weapon/KBWeaponComponent.h"
#include "KBUtils.h"

float UKBPlayerHUDWidget::GetHealthPercent()
{
    if (!HealthComponent && !InitHealthComponent()) return 0.f;

    return HealthComponent->GetHealthPercent();
}

bool UKBPlayerHUDWidget::GetUIWeaponData(FUIWeaponData& UIWeaponData)
{
    if (!WeaponComponent && !InitWeaponComponent()) return false;

    return WeaponComponent->GetUIWeaponData(UIWeaponData);
}

bool UKBPlayerHUDWidget::GetWeaponAmmoData(FWeaponAmmo& WeaponAmmoData)
{
    if (!WeaponComponent && !InitWeaponComponent()) return false;

    return WeaponComponent->GetCurrentAmmoData(WeaponAmmoData);
}

bool UKBPlayerHUDWidget::IsPlayerAlive()
{
    if (!HealthComponent && !InitHealthComponent()) return false;

    return !HealthComponent->IsDeath();
}

bool UKBPlayerHUDWidget::IsPlayerSpectating()
{
    const auto Controller = GetOwningPlayer();

    return Controller && Controller->GetStateName() == NAME_Spectating;
}

bool UKBPlayerHUDWidget::Initialize()
{
    HealthComponent = KBUtils::GetPlayerComponent<UKBHealthComponent>(GetOwningPlayerPawn());

    if (!HealthComponent) return true;

    HealthComponent->OnDamaged.AddUObject(this, &UKBPlayerHUDWidget::OnTakeDamage);

    return Super::Initialize();
}

bool UKBPlayerHUDWidget::InitWeaponComponent()
{
    const APawn* Owner = GetOwningPlayerPawn();
    if (!Owner) return false;

    UActorComponent* ActorComponent = Owner->GetComponentByClass(UKBWeaponComponent::StaticClass());
    WeaponComponent = Cast<UKBWeaponComponent>(ActorComponent);

    if (WeaponComponent) return true;

    return false;
}

bool UKBPlayerHUDWidget::InitHealthComponent()
{
    HealthComponent = KBUtils::GetPlayerComponent<UKBHealthComponent>(GetOwningPlayerPawn());

    if (HealthComponent) return true;

    return false;
}