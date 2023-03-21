// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/KBPlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogKBPlayerState, All, All);

void AKBPlayerState::LogInfo()
{
    UE_LOG(LogKBPlayerState, Display, TEXT("TeamID: %i, Kills: %i, Deaths: %i"), TeamID, GetKills(), GetDeaths());
}
