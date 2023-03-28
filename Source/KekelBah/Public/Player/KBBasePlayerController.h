// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "KBBasePlayerController.generated.h"

class UKBRespawnComponent;

UCLASS()
class KEKELBAH_API AKBBasePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
    AKBBasePlayerController();

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UKBRespawnComponent* RespawnComponent;
};
