// Fill out your copyright notice in the Description page of Project Settings.


#include "Menu/UI/KBMenuUserWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "Sound/SoundCue.h"

void UKBMenuUserWidget::NativeOnInitialized()
{
    if (StartGameButton)
    {
        StartGameButton->OnClicked.AddDynamic(this, &UKBMenuUserWidget::OnStartGame);
    }
    if (QuitGameButton)
    {
        QuitGameButton->OnClicked.AddDynamic(this, &UKBMenuUserWidget::OnQuidGame);
    }
    Super::NativeOnInitialized();
}

void UKBMenuUserWidget::OnStartGame()
{
    UGameplayStatics::PlaySound2D(this, StartGameSound);
    const FName LevelName = "TestLevel";
    UGameplayStatics::OpenLevel(this, LevelName);
}

void UKBMenuUserWidget::OnQuidGame()
{
    UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}
