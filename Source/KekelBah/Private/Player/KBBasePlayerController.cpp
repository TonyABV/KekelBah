// Fill out your copyright notice in the Description page of Project Settings.


#include "KBBasePlayerController.h"
#include "KBGameModeBase.h"
#include "KBRespawnComponent.h"
#include "GameFramework/GameModeBase.h"
#include "KBGameInstance.h"


AKBBasePlayerController::AKBBasePlayerController()
{
    RespawnComponent = CreateDefaultSubobject<UKBRespawnComponent>("RespawnComponent");
}

void AKBBasePlayerController::BeginPlay()
{
    Super::BeginPlay();
    
    if (GetWorld()->GetAuthGameMode<AKBGameModeBase>())
    {
        GetWorld()->GetAuthGameMode<AKBGameModeBase>()->OnMatchStateChanged.AddUObject(this, &AKBBasePlayerController::OnMatchStateChanged);
    }
}

void AKBBasePlayerController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (!InputComponent) return;

    InputComponent->BindAction("PauseGame", EInputEvent::IE_Pressed, this, &AKBBasePlayerController::OnPause);
    InputComponent->BindAction("Mute", EInputEvent::IE_Pressed, this, &AKBBasePlayerController::OnMute);
}

void AKBBasePlayerController::OnPause()
{
    if (GetWorld()->GetAuthGameMode())
    {
        GetWorld()->GetAuthGameMode()->SetPause(this);
    }
}

void AKBBasePlayerController::OnMute()
{
    if (GetWorld()->GetGameInstance<UKBGameInstance>())
    {
        GetWorld()->GetGameInstance<UKBGameInstance>()->ToggleMasterSound();
    }
}

void AKBBasePlayerController::OnMatchStateChanged(EKBMatchState NewState)
{
    if (NewState == EKBMatchState::Pause || NewState == EKBMatchState::GameOver)
    {
        SetInputMode(FInputModeUIOnly());
        SetShowMouseCursor(true);
    }
    else
    {
        SetInputMode(FInputModeGameOnly());
        SetShowMouseCursor(false);
    }
}
