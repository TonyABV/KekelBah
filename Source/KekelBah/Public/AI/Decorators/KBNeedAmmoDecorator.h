// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "KBNeedAmmoDecorator.generated.h"

class AKBBaseWeaponActor;

UCLASS()
class KEKELBAH_API UKBNeedAmmoDecorator : public UBTDecorator
{
	GENERATED_BODY()

public:

    UKBNeedAmmoDecorator();

	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    TSubclassOf<AKBBaseWeaponActor> WeaponClass;

};
