// Fill out your copyright notice in the Description page of Project Settings.


#include "KBPauseWidget.h"

#include "Components/Button.h"
#include "GameFramework/GameModeBase.h"

bool UKBPauseWidget::Initialize()
{
    const bool InitializeStatus = Super::Initialize();

    if (ClearPauseButton)
    {
        ClearPauseButton->OnClicked.AddDynamic(this, &UKBPauseWidget::OnClearPause);
    }
    return InitializeStatus;
}

void UKBPauseWidget::OnClearPause()
{
    if (GetWorld()->GetAuthGameMode())
    {
        GetWorld()->GetAuthGameMode()->ClearPause();
    }
}
