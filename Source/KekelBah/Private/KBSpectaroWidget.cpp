// Fill out your copyright notice in the Description page of Project Settings.

#include "KBSpectaroWidget.h"
#include "KBUtils.h"
#include "KBRespawnComponent.h"

bool UKBSpectaroWidget::GetRespawnTime(int32& Time)
{
    const UKBRespawnComponent* RespawnComponent = KBUtils::GetPlayerComponent<UKBRespawnComponent>(GetOwningPlayer());

    if (!RespawnComponent || !RespawnComponent->IsRespawnInProgress()) return false;

    Time = RespawnComponent->GetTimeToRespawn();

    return true;
}
