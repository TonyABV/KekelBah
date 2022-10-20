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

	virtual void DrawHUD() override;
};
