// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KBSpectaroWidget.generated.h"

/**
 * 
 */
UCLASS()
class KEKELBAH_API UKBSpectaroWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetRespawnTime(int32& Time);
};
