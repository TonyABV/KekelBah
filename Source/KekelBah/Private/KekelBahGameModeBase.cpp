// Copyright Epic Games, Inc. All Rights Reserved.


#include "KekelBahGameModeBase.h"
#include "KBBaseCharacter.h"
#include "KBBasePlayerController.h"

AKekelBahGameModeBase::AKekelBahGameModeBase()
{
    DefaultPawnClass = AKBBaseCharacter::StaticClass();
    PlayerControllerClass = AKBBasePlayerController::StaticClass();
}
