// Fill out your copyright notice in the Description page of Project Settings.


#include "KBPlayerHUDWidget.h"

#include "KBGameModeBase.h"
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

bool UKBPlayerHUDWidget::GetPlayerKills(int32& Kills)
{
    if (!PlayerState) return false;
    Kills = PlayerState->GetKills();
    return true;
}

bool UKBPlayerHUDWidget::GetPlayerDeaths(int32& Deaths)
{
    if (!PlayerState) return false;
    Deaths = PlayerState->GetDeaths();
    return true;
}

bool UKBPlayerHUDWidget::GetRoundTime(float& RoundTime)
{
    if (!GameMode) return false;

    RoundTime = GameMode->GetCurrentRoundTime();

    return true;
}

bool UKBPlayerHUDWidget::GetCurrentRound(int32& CurrentRound)
{
    if (!GameMode) return false;

    CurrentRound = GameMode->GetCurrentRound();

    return true;
}

bool UKBPlayerHUDWidget::GetRoundNum(int32& RoundNum)
{
    if (!GameMode) return false;

    RoundNum = GameMode->GetMaxRound();

    return true;
}

bool UKBPlayerHUDWidget::Initialize()
{
    if (!GetOwningPlayer()) return false;

    GetOwningPlayer()->GetOnNewPawnNotifier().AddUObject(this, &UKBPlayerHUDWidget::OnNewPawn);
    OnNewPawn(GetOwningPlayerPawn());

    PlayerState = GetOwningPlayerState<AKBPlayerState>();

    if (GetWorld()) GameMode = Cast<AKBGameModeBase>(GetWorld()->GetAuthGameMode());

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

void UKBPlayerHUDWidget::OnNewPawn(APawn* NewPawn)
{
    if (!NewPawn) return;

    HealthComponent = KBUtils::GetPlayerComponent<UKBHealthComponent>(NewPawn);

    if (!HealthComponent) return;

    HealthComponent->OnDamaged.AddUObject(this, &UKBPlayerHUDWidget::OnTakeDamage);
}
