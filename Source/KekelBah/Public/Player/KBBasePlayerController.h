// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "KBCoreTypes.h"
#include "KBBasePlayerController.generated.h"

class UKBRespawnComponent;

UCLASS()
class KEKELBAH_API AKBBasePlayerController : public APlayerController
{
	GENERATED_BODY()

public:

    AKBBasePlayerController();

	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UKBRespawnComponent* RespawnComponent;

	virtual void SetupInputComponent() override;

    void OnPause();

    void OnMute();

	void OnMatchStateChanged(EKBMatchState NewState);
};
