// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/Components/KBRespawnComponent.h"
#include "KBGameModeBase.h"

UKBRespawnComponent::UKBRespawnComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UKBRespawnComponent::RespawnWithDelay(int32 RespawnTime)
{
	GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &UKBRespawnComponent::Respawn, RespawnTime, false);
}

void UKBRespawnComponent::Respawn()
{
    const auto GameMode = GetWorld()->GetAuthGameMode<AKBGameModeBase>();
    if (!GameMode) return;

    GameMode->RespawnRequest(GetOwner<AController>());
}
