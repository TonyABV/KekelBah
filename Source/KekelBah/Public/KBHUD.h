// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "KBCoreTypes.h"
#include "KBHUD.generated.h"

/**
 * 
 */
UCLASS()
class KEKELBAH_API AKBHUD : public AHUD
{
	GENERATED_BODY()


public:

	virtual void DrawHUD() override;

	virtual void BeginPlay() override;

protected:

	UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UUserWidget> PlayerHUDWidgetClass;
	UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UUserWidget> PauseHUDWidgetClass;
    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UUserWidget>GameOverWidget;

protected:

	TMap<EKBMatchState, UUserWidget*> Widgets;

	UUserWidget* CurrentWidget = nullptr;

	void DrawCross();

    void OnMatchStateChanged(EKBMatchState NewState);
};
