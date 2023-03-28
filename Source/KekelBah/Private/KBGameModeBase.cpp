// Fill out your copyright notice in the Description page of Project Settings.

#include "KBGameModeBase.h"
#include "KBBaseCharacter.h"
#include "KBBasePlayerController.h"
#include "KBHUD.h"
#include "AIController.h"
#include "KBPlayerState.h"
#include "KBUtils.h"
#include "KBRespawnComponent.h"
#include "EngineUtils.h"

DEFINE_LOG_CATEGORY_STATIC(LogKBGameMode, All, All);

AKBGameModeBase::AKBGameModeBase()
{
    DefaultPawnClass = AKBBaseCharacter::StaticClass();
    PlayerControllerClass = AKBBasePlayerController::StaticClass();
    HUDClass = AKBHUD::StaticClass();

    PlayerStateClass = AKBPlayerState::StaticClass();
}

void AKBGameModeBase::StartPlay()
{
    Super::StartPlay();

    SpawnBots();

    CreateTeamsInfo();

    CurrentRound = 1;
    StartRound();
}

UClass* AKBGameModeBase::GetDefaultPawnClassForController_Implementation(AController* InController)
{
    if (InController && InController->IsA(AIControllerClass))
    {
        return AIPawnClass;
    }

    return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void AKBGameModeBase::Killed(AController* KillerController, AController* VictimController)
{
    AKBPlayerState* KillerState = KillerController ? KillerController->GetPlayerState<AKBPlayerState>() : nullptr;
    AKBPlayerState* VictimState = VictimController ? VictimController->GetPlayerState<AKBPlayerState>() : nullptr;

    if (KillerState) KillerState->AddKill();
    if (VictimState) VictimState->AddDeath();

    StartRespawn(VictimController);
}

float AKBGameModeBase::GetCurrentRoundTime() const
{
    return GetWorldTimerManager().GetTimerRemaining(StartRoundTimerHandle);
}

void AKBGameModeBase::StartRespawn(AController* Controller)
{
    if (GetCurrentRoundTime() < GameData.RespawnTime) return;

    UKBRespawnComponent* RespawnComponent = KBUtils::GetPlayerComponent<UKBRespawnComponent>(Controller);

    if (!RespawnComponent) return;

    RespawnComponent->RespawnWithDelay(GameData.RespawnTime);
}

void AKBGameModeBase::RespawnRequest(AController* Controller)
{
    ResetOnePlayer(Controller);
}

void AKBGameModeBase::SpawnBots()
{
    if (!AIControllerClass) return;

    for (int32 n = 0; n < GameData.PlayersNum - 1; ++n)
    {
        FActorSpawnParameters SpawnInfo;
        SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        AAIController* NewController = GetWorld()->SpawnActor<AAIController>(AIControllerClass, SpawnInfo);
        RestartPlayer(NewController);
    }
}

void AKBGameModeBase::StartRound()
{

    GetWorldTimerManager().SetTimer(StartRoundTimerHandle,  //
        this,                                               //
        &AKBGameModeBase::EndRound,                         //
        GameData.RoundTime,                                 //
        true);
}

void AKBGameModeBase::EndRound()
{
    UE_LOG(LogKBGameMode, Display, TEXT("Round: %i/%i"), CurrentRound, GameData.RoundNum);

    GetWorldTimerManager().ClearTimer(StartRoundTimerHandle);

    if (CurrentRound + 1 != GameData.RoundNum + 1)
    {
        UE_LOG(LogKBGameMode, Display, TEXT("----End Round----"));
        ResetPlayers();
        StartRound();
        ++CurrentRound;
    }
    else
    {
        GameOver();
    }
}

void AKBGameModeBase::GameOver()
{
    for (auto Pawn: TActorRange<APawn>(GetWorld()))
    {
        if (Pawn)
        {
            Pawn->TurnOff();
            Pawn->DisableInput(nullptr);
        }
    }
    LogPlayerInfo();
    UE_LOG(LogKBGameMode, Display, TEXT("----EndGame----"));
}

void AKBGameModeBase::ResetPlayers()
{
    if (!GetWorld()) return;

    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        ResetOnePlayer(It->Get());
    }
}

void AKBGameModeBase::ResetOnePlayer(AController* Controller)
{
    if (Controller && Controller->GetPawn())
    {
        Controller->GetPawn()->Reset();
    }
    RestartPlayer(Controller);
    SetPlayerColor(Controller);
}

void AKBGameModeBase::CreateTeamsInfo()
{
    if (!GetWorld()) return;

    int32 TeamID = 1;

    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        AController* Controller = It->Get();
        if (!Controller) continue;
        ;

        AKBPlayerState* PlayerState = Controller->GetPlayerState<AKBPlayerState>();
        if (!PlayerState) continue;

        PlayerState->SetTeamColor(DetermineColorByTeamID(TeamID));
        PlayerState->SetTeamID(TeamID);
        SetPlayerColor(Controller);

        TeamID = TeamID == 1 ? 2 : 1;
    }
}

FLinearColor AKBGameModeBase::DetermineColorByTeamID(int32 TeamID) const
{
    if (TeamID - 1 < GameData.TeamColors.Num())
    {
        return GameData.TeamColors[TeamID - 1];
    }
    return GameData.DefaultTeamColor;
}

void AKBGameModeBase::SetPlayerColor(AController* Controller)
{
    if (!Controller) return;

    const auto Char = Controller->GetPawn<AKBBaseCharacter>();
    if (!Char) return;

    AKBPlayerState* PlayerState = Controller->GetPlayerState<AKBPlayerState>();
    if (!PlayerState) return;
    ;

    Char->SetPlayerColor(PlayerState->GetTeamColor());
}

void AKBGameModeBase::LogPlayerInfo()
{
    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        AController* Controller = It->Get();
        if (!Controller) continue;

        AKBPlayerState* PlayerState = Controller->GetPlayerState<AKBPlayerState>();
        if (!PlayerState) continue;

        PlayerState->LogInfo();
    }
}
