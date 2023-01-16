// Fill out your copyright notice in the Description page of Project Settings.


#include "KBPlayerHUDWidget.h"
#include "Player/Components/KBHealthComponent.h"

float UKBPlayerHUDWidget::GetHealthPercent() const
{
    const APawn* Owner = GetOwningPlayerPawn();
    if (!Owner) return 0.f;

    UActorComponent* ActorComponent = Owner->GetComponentByClass(UKBHealthComponent::StaticClass());
    UKBHealthComponent* HealthComponent = Cast<UKBHealthComponent>(ActorComponent);

    if (!HealthComponent) return 0.f;

    return HealthComponent->GetHealthPercent();
}
