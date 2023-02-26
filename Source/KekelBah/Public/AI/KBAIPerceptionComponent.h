// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "KBAIPerceptionComponent.generated.h"

/**
 * 
 */
UCLASS()
class KEKELBAH_API UKBAIPerceptionComponent : public UAIPerceptionComponent
{
    GENERATED_BODY()

public:

    AActor* GetClosestEnemy() const;
};
