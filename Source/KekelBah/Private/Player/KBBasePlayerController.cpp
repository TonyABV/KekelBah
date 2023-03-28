// Fill out your copyright notice in the Description page of Project Settings.


#include "KBBasePlayerController.h"
#include "KBRespawnComponent.h"

AKBBasePlayerController::AKBBasePlayerController()
{
    RespawnComponent = CreateDefaultSubobject<UKBRespawnComponent>("RespawnComponent");
}
