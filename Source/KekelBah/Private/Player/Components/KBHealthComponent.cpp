// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Components/KBHealthComponent.h"
#include "KBAcidDamageType.h"

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

	Health = MaxHealth;

	if (IsValid(GetOwner()))
	{
        GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UKBHealthComponent::OnTakeDamageHandle);
	}
}

void UKBHealthComponent::OnTakeDamageHandle(
    AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
    if (Damage <= 0.f || IsDeath()) return;
	
    Health = FMath::Clamp( Health - Damage, 0.f, MaxHealth);

	OnHealthChanged.Broadcast(Health);

	if (Health == 0.f) OnDead.Broadcast();

	if (IsValid(DamageType))
	{
        if(DamageType->GetClass()->IsChildOf(UKBAcidDamageType::StaticClass()))
        {
            UE_LOG(LogHealthComponent, Log, TEXT("Actor: %s took ACID damage."), *(GetOwner()->GetName()), Damage);
        }
	}

	UE_LOG(LogHealthComponent, Log, TEXT("Actor: %s, Damege: %f"), *(GetOwner()->GetName()), Damage);
}