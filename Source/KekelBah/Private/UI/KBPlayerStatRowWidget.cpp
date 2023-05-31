// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/KBPlayerStatRowWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

void UKBPlayerStatRowWidget::SetPlayerName(const FText& Name)
{
    if (!NameText) return;
    NameText->SetText(Name);
}

void UKBPlayerStatRowWidget::SetKills(const FText& Kills)
{
    if (!KillsText) return;
    KillsText->SetText(Kills);
}

void UKBPlayerStatRowWidget::SetDeaths(const FText& Deaths)
{
    if (!DeathText) return;
    DeathText->SetText(Deaths);
}
void UKBPlayerStatRowWidget::SetTeamID(const FText& TeamID)
{
    if (!TeamText) return;
    TeamText->SetText(TeamID);
}

void UKBPlayerStatRowWidget::SetHighLighterVisibility(bool IsVisible)
{
    HighLighter->SetVisibility(IsVisible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);
}
