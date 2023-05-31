// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KBPlayerStatRowWidget.generated.h"

class UImage;
class UTextBlock;

UCLASS()
class KEKELBAH_API UKBPlayerStatRowWidget : public UUserWidget
{
    GENERATED_BODY()

public:

    void SetPlayerName(const FText& Name);
    void SetKills(const FText& Kills);
    void SetDeaths(const FText& Deaths);
    void SetTeamID(const FText& TeamID);
    void SetHighLighterVisibility(bool IsVisible);

protected:

	UPROPERTY(meta = (BindWidget))
    UImage* HighLighter;

	UPROPERTY(meta = (BindWidget))
    UTextBlock* NameText;

	UPROPERTY(meta = (BindWidget))
    UTextBlock* KillsText;

	UPROPERTY(meta = (BindWidget))
    UTextBlock* DeathText;

	UPROPERTY(meta = (BindWidget))
    UTextBlock* TeamText;

};
