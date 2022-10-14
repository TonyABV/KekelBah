// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Components/KBHealthComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All);

UKBHealthComponent::UKBHealthComponent()
{

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
    Health -= Damage;

	UE_LOG(LogHealthComponent, Log, TEXT("Actor: %s, Damege: %f"), *(GetOwner()->GetName()), Damage);
}