// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Components/KBHealthComponent.h"
#include "KBAcidDamageType.h"
#include "Camera/CameraShakeBase.h"
#include "KBGameModeBase.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All);

UKBHealthComponent::UKBHealthComponent()
{

}


bool UKBHealthComponent::IsDeath()
{
    return Health <= 0;
}

// Called when the game starts
void UKBHealthComponent::BeginPlay()
{
	Super::BeginPlay();

    check(CameSake);

	Health = MaxHealth;

	if (IsValid(GetOwner()))
	{
        GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UKBHealthComponent::OnTakeDamageHandle);
	}

	if (bAutoHealEnable)
	{
        OnDamaged.AddUObject(this, &UKBHealthComponent::TryOnAutoHeal);
        OnDead.AddUObject(this, &UKBHealthComponent::StopAutoHeal);
        OnFullHealth.AddUObject(this, &UKBHealthComponent::StopAutoHeal);
	}	
}

void UKBHealthComponent::OnTakeDamageHandle(
    AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
    if (Damage <= 0.f || IsDeath()) return;
	
    Health = FMath::Clamp( Health - Damage, 0.f, MaxHealth);

    OnDamaged.Broadcast();

	OnHealthChanged.Broadcast(Health);

	if (FMath::IsNearlyZero(Health))
    {
        Killed(InstigatedBy);
        OnDead.Broadcast();
    }

	if (IsValid(DamageType))
	{
        if(DamageType->GetClass()->IsChildOf(UKBAcidDamageType::StaticClass()))
        {
            UE_LOG(LogHealthComponent, Log, TEXT("Actor: %s took ACID damage."), *(GetOwner()->GetName()), Damage);
        }
	}

    PlayCameraShake();
}

void UKBHealthComponent::TryOnAutoHeal()
{
    if (!IsValid(GetWorld())) return;

    auto& TimerManager = GetWorld()->GetTimerManager();

    TimerManager.ClearTimer(AutoHealHandle);

    TimerManager.SetTimer(
        AutoHealHandle, [=]() { Heal(AutoHealValue); }, AutoHealSpan, true, AutoHealDelay);

}

float UKBHealthComponent::GetHealthPercent() const
{
    return Health/MaxHealth;
}

bool UKBHealthComponent::IsFullHealth() const
{
    return FMath::IsNearlyEqual(Health, MaxHealth);
}

bool UKBHealthComponent::TryAddHealth(float HealthAmount)
{
    if (HealthAmount <= 0.f || IsFullHealth()) return false;
    Heal(HealthAmount);
    return true;
}

void UKBHealthComponent::Heal(const float Value)
{
    if (MaxHealth != Health)
    {
        Health = FMath::Clamp(Health + Value, 0.f, MaxHealth);
    }

    OnHealthChanged.Broadcast(Health);

    if (FMath::IsNearlyEqual(Health, MaxHealth))
    {
        OnFullHealth.Broadcast();
    }
}

void UKBHealthComponent::StopAutoHeal()
{
    GetWorld()->GetTimerManager().ClearTimer(AutoHealHandle);
}

void UKBHealthComponent::PlayCameraShake()
{
    if (IsDeath()) return;

    APawn* Pawn = GetOwner<APawn>();
    if (!Pawn)  return;

    const auto Controller = Pawn->GetController<APlayerController>();
    if (!Controller || !Controller->PlayerCameraManager) return;
    Controller->PlayerCameraManager->StartCameraShake(CameSake);
}

void UKBHealthComponent::Killed(AController* KillerController)
{
    AKBGameModeBase* GameMode = Cast<AKBGameModeBase>(GetWorld()->GetAuthGameMode());
    if (!GameMode) return;

    const auto Player = GetOwner();
    if (!Player) return;

    GameMode->Killed(KillerController, Cast<AController>(Player->GetOwner()));
}
