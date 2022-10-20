// Copyright Epic Games, Inc. All Rights Reserved.


#include "KekelBahGameModeBase.h"
#include "KBBaseCharacter.h"
#include "KBBasePlayerController.h"
#include "KBHUD.h"

AKekelBahGameModeBase::AKekelBahGameModeBase()
{
    DefaultPawnClass = AKBBaseCharacter::StaticClass();
    PlayerControllerClass = AKBBasePlayerController::StaticClass();
    HUDClass = AKBHUD::StaticClass();
}
