// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/KBMenuPlayerController.h"

void AKBMenuPlayerController::BeginPlay()
{
    Super::BeginPlay();

    SetInputMode(FInputModeUIOnly());
    SetShowMouseCursor(true);
}
