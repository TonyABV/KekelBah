// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KBMenuUserWidget.generated.h"

class UButton;
class USoundCue;

UCLASS()
class KEKELBAH_API UKBMenuUserWidget : public UUserWidget
{
	GENERATED_BODY()

protected:

	virtual void NativeOnInitialized() override;

	UPROPERTY(meta = (BindWidget))
    UButton* StartGameButton;

	UPROPERTY(meta = (BindWidget))
    UButton* QuitGameButton;

	UFUNCTION()
    void OnStartGame();

	UFUNCTION()
    void OnQuidGame();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
    USoundCue* StartGameSound;
};
