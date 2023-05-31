// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "KBSoundFuncLib.generated.h"

class USoundClass;

UCLASS()
class KEKELBAH_API UKBSoundFuncLib : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
    static void SetSoundClassVolume(USoundClass* SoundClass, float Volume);
		
	UFUNCTION(BlueprintCallable)
    static void ToggleSoundClass(USoundClass* SoundClass);
};
