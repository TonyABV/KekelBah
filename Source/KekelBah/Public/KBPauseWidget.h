// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KBPauseWidget.generated.h"

class UButton;

UCLASS()
class KEKELBAH_API UKBPauseWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual bool Initialize() override;

	UFUNCTION()
	void OnClearPause();

	UPROPERTY(meta = (BindWidget));
    UButton* ClearPauseButton;
};
