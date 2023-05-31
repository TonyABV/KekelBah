// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/KBGameOverWidget.h"
#include "KBGameModeBase.h"
#include "KBPlayerState.h"
#include "Components/VerticalBox.h"
#include "Renderer/Private/SceneCore.h"
#include "UI/KBPlayerStatRowWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

bool UKBGameOverWidget::Initialize()
{
    if (GetWorld()->GetAuthGameMode<AKBGameModeBase>())
    {
        GetWorld()->GetAuthGameMode<AKBGameModeBase>()->OnMatchStateChanged.AddUObject(this, &UKBGameOverWidget::OnMatchStateChanged);
    }

    if (!ResetLevelButton) Super::Initialize();
    ResetLevelButton->OnClicked.AddDynamic(this, &UKBGameOverWidget::OnResetLevel);
    return Super::Initialize();
}

void UKBGameOverWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

}

void UKBGameOverWidget::OnMatchStateChanged(EKBMatchState State)
{
    if (State == EKBMatchState::GameOver)
    {
        UpdatePlayerState();
    }
}

void UKBGameOverWidget::UpdatePlayerState()
{
    if (!PlayerStateBox) return;
    PlayerStateBox->ClearChildren();

    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const auto Controller = It->Get();
        if (!Controller) continue;

        const auto PlayerState = Controller->GetPlayerState<AKBPlayerState>();
        if (!PlayerState) continue;

        auto Widget = CreateWidget<UKBPlayerStatRowWidget>(GetWorld(), PlayerStatWidgetClass);
        if (!Widget) continue;

        Widget->SetPlayerName(FText::FromString(PlayerState->GetPlayerName()));
        Widget->SetKills(FText::FromString(FString::FromInt(PlayerState->GetKills())));
        Widget->SetHighLighterVisibility(Controller->IsPlayerController());

        PlayerStateBox->AddChildToVerticalBox(Widget);
    }
}

void UKBGameOverWidget::OnResetLevel()
{
    FName LevelName = FName(UGameplayStatics::GetCurrentLevelName(this));
    UGameplayStatics::OpenLevel(this, LevelName);
}
