// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "KBHealthPercentDecorator.generated.h"

/**
 * 
 */
UCLASS()
class KEKELBAH_API UKBHealthPercentDecorator : public UBTDecorator
{
	GENERATED_BODY()

public:

	UKBHealthPercentDecorator();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float HealthPercent = 0.6;
};
