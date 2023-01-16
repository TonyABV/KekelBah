// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
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

protected:

	void DrawCross();

};
