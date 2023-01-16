// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KBPlayerHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class KEKELBAH_API UKBPlayerHUDWidget : public UUserWidget
{
    GENERATED_BODY()

public:

    UFUNCTION(BlueprintCallable, Category = "UI")
    float GetHealthPercent() const;
};
