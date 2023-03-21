// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "KBPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class KEKELBAH_API AKBPlayerState : public APlayerState
{
	GENERATED_BODY()

public:

	int32 GetTeamID() const { return TeamID; }
    void SetTeamID(int32 NewTeamID) { TeamID = NewTeamID; }

	FLinearColor GetTeamColor() const { return TeamColor; }
    void SetTeamColor(const FLinearColor& NewTeamColor) { TeamColor = NewTeamColor; }

	void AddKill() { ++KillsNum; }
    int32 GetKills() const { return KillsNum; }

	void AddDeath() { ++DeathsNum; }
    int32 GetDeaths() const { return DeathsNum; }

	void LogInfo();

private:

	int32 TeamID;

	FLinearColor TeamColor;

	int32 KillsNum = 0;
    int32 DeathsNum = 0;

};
