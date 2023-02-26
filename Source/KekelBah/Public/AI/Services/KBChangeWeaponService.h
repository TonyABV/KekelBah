// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "KBChangeWeaponService.generated.h"

/**
 * 
 */
UCLASS()
class KEKELBAH_API UKBChangeWeaponService : public UBTService
{
	GENERATED_BODY()
	
public:

	UKBChangeWeaponService();

	UPROPERTY(EditAnywhere, Category = "AI", meta = (ClampMin = "0.0", ClampMax = "1.0"))
    float Probability = 0.5;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
};
