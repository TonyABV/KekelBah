// Fill out your copyright notice in the Description page of Project Settings.

#include "KBGameModeBase.h"
#include "KBBaseCharacter.h"
#include "KBBasePlayerController.h"
#include "KBHUD.h"
#include "AIController.h"
#include "KBPlayerState.h"

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
    RoundCountDown = GameData.RoundTime;

    GetWorldTimerManager().SetTimer(StartRoundTimerHandle,  //
        this,                                               //
        &AKBGameModeBase::GameTimerUpdate,                  //
        1.f,                                                //
        true);
}

void AKBGameModeBase::GameTimerUpdate()
{
    UE_LOG(LogKBGameMode, Display, TEXT("Time: %i, Round: %i/%i"), RoundCountDown, CurrentRound, GameData.RoundNum);
    
    if (--RoundCountDown == 0)
    {
        GetWorldTimerManager().ClearTimer(StartRoundTimerHandle);

        if (++CurrentRound != GameData.RoundNum + 1)
        {
            UE_LOG(LogKBGameMode, Display, TEXT("----End Round----"));
            ResetPlayers();
            StartRound();
        }
        else
        {
            UE_LOG(LogKBGameMode, Display, TEXT("----EndGame----"));
        }
    }
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
        if (!Controller) continue;;

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
    if (!PlayerState) return;;

    Char->SetPlayerColor(PlayerState->GetTeamColor());
}
