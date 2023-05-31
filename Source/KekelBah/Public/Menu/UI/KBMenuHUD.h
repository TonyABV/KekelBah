// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "KBMenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class KEKELBAH_API AKBMenuHUD : public AHUD
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

public:
    UPROPERTY(EditDefaultsOnly, Category = "UI")
    TSubclassOf<UUserWidget> MenuWidgetClass;
};
