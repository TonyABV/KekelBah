// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "KBGameInstance.generated.h"

class USoundClass;

UCLASS()
class KEKELBAH_API UKBGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:

	void ToggleMasterSound();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
    USoundClass* MasterSoundClass;

};
