// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "KBRespawnComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KEKELBAH_API UKBRespawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UKBRespawnComponent();

	void RespawnWithDelay(int32 RespawnTime);

	int32 GetTimeToRespawn() const { return GetWorld()->GetTimerManager().GetTimerRemaining(RespawnTimerHandle); };

	bool IsRespawnInProgress() const { return GetWorld()->GetTimerManager().IsTimerActive(RespawnTimerHandle); }

private:

	FTimerHandle RespawnTimerHandle;
	
	void Respawn();

};
