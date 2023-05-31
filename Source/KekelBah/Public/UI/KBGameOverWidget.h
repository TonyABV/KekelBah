// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KBCoreTypes.h"
#include "KBGameOverWidget.generated.h"


class UVerticalBox;
class UButton;
 
UCLASS()
class KEKELBAH_API UKBGameOverWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

	virtual void NativeOnInitialized() override;

protected:

	UPROPERTY(meta = (BindWidget))
    UVerticalBox* PlayerStateBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PlayerStatWidgetClass;

	UPROPERTY(meta = (BindWidget))
    UButton* ResetLevelButton;

private:
    void OnMatchStateChanged(EKBMatchState State);
    void UpdatePlayerState();

UFUNCTION()
void OnResetLevel();

};
