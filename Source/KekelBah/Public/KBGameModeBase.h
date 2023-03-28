// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "KBCoreTypes.h"
#include "KBGameModeBase.generated.h"

class AAIController;

UCLASS()
class KEKELBAH_API AKBGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	AKBGameModeBase();

	virtual void StartPlay() override;

	virtual UClass* GetDefaultPawnClassForController_Implementation(AController* InController) override;

	void Killed(AController* KillerController, AController* VictimController);

	int32 GetCurrentRound() const { return CurrentRound; }

	int32 GetMaxRound() const { return GameData.RoundNum; }

	float GetCurrentRoundTime() const;

	void StartRespawn(AController* Controller);

    void RespawnRequest(AController* Controller);

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	TSubclassOf<AAIController> AIControllerClass;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
	FGameData GameData;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
    TSubclassOf<APawn> AIPawnClass;

private:

	int32 CurrentRound = 0;
	FTimerHandle StartRoundTimerHandle;

	void SpawnBots();
    void StartRound();
    void EndRound();

	void GameOver();

	void ResetPlayers();
    void ResetOnePlayer(AController* Controller);

	void CreateTeamsInfo();
    FLinearColor DetermineColorByTeamID(int32 TeamID) const;
    void SetPlayerColor(AController* Controller);

	void LogPlayerInfo();
};
