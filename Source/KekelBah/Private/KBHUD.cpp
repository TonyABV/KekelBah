// Fill out your copyright notice in the Description page of Project Settings.


#include "KBHUD.h"

#include "KBGameModeBase.h"
#include "Engine/Canvas.h"
#include "Blueprint/UserWidget.h"

DECLARE_LOG_CATEGORY_CLASS(LogAKBHUD, All, All);

void AKBHUD::DrawHUD()
{
    Super::DrawHUD();
    
}

void AKBHUD::BeginPlay()
{
    Super::BeginPlay();

    Widgets.Add(EKBMatchState::InProgress, CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass));
    Widgets.Add(EKBMatchState::Pause, CreateWidget<UUserWidget>(GetWorld(), PauseHUDWidgetClass));
    Widgets.Add(EKBMatchState::GameOver, CreateWidget<UUserWidget>(GetWorld(), GameOverWidget));

    for (const auto Widget : Widgets)
    {
        if (Widget.Value)
        {
            Widget.Value->AddToViewport();
            Widget.Value->SetVisibility(ESlateVisibility::Hidden);
        }
    }
    
    if (GetWorld()->GetAuthGameMode<AKBGameModeBase>())
    {
        GetWorld()->GetAuthGameMode<AKBGameModeBase>()->OnMatchStateChanged.AddUObject(this, &AKBHUD::OnMatchStateChanged);
    }
}

void AKBHUD::DrawCross()
{
    const TPair<float, float> X_Y_Center(Canvas->SizeX * 0.5, Canvas->SizeY * 0.5);

    DrawLine(X_Y_Center.Key + 10.f, X_Y_Center.Value, X_Y_Center.Key + X_Y_Center.Key * 0.05,
        X_Y_Center.Value, FLinearColor::Black, 3.f);

    DrawLine(X_Y_Center.Key - 10.f, X_Y_Center.Value, X_Y_Center.Key - X_Y_Center.Key * 0.05, X_Y_Center.Value, FLinearColor::Black, 3.f);
    DrawLine(X_Y_Center.Key, X_Y_Center.Value + 10.f, X_Y_Center.Key, X_Y_Center.Value + X_Y_Center.Key * 0.05, FLinearColor::Black, 3.f);
    DrawLine(X_Y_Center.Key, X_Y_Center.Value - 10.f, X_Y_Center.Key, X_Y_Center.Value - X_Y_Center.Key * 0.05, FLinearColor::Black, 3.f);
}

void AKBHUD::OnMatchStateChanged(EKBMatchState NewState)
{
    if (CurrentWidget)
    {
        CurrentWidget->SetVisibility(ESlateVisibility::Hidden);
    }

    if (Widgets.Contains(NewState))
    {
        CurrentWidget = Widgets[NewState];
    }

    if (CurrentWidget)
    {
        CurrentWidget->SetVisibility(ESlateVisibility::Visible);
    }

    UE_LOG(LogAKBHUD, Display, TEXT("State: %s"), *UEnum::GetValueAsString(NewState));
}
