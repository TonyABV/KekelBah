// Fill out your copyright notice in the Description page of Project Settings.


#include "KBHUD.h"

#include "Engine/Canvas.h"
#include "Blueprint/UserWidget.h"

void AKBHUD::DrawHUD()
{
    Super::DrawHUD();

    DrawCross();
}

void AKBHUD::BeginPlay()
{
    Super::BeginPlay();

    const auto PlayerHUDWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass);
    if (!PlayerHUDWidget) return;

    PlayerHUDWidget->AddToViewport();
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
