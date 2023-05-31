// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/KBMenuGameModeBase.h"
#include "Menu/KBMenuPlayerController.h"
#include "Menu/UI/KBMenuHUD.h"

AKBMenuGameModeBase::AKBMenuGameModeBase()
{
    PlayerControllerClass = AKBMenuPlayerController::StaticClass();
    HUDClass = AKBMenuHUD::StaticClass();
}
