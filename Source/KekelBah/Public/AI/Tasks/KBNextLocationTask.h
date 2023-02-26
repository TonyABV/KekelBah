// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "KBNextLocationTask.generated.h"

/**
 * 
 */
UCLASS()
class KEKELBAH_API UKBNextLocationTask : public UBTTaskNode
{
    GENERATED_BODY()

    UKBNextLocationTask();

    virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float Radius = 50.f;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector AimLocationKey;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    bool bSelfCenter = true;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (EditCondition = "!bSelfCenter"))
    FBlackboardKeySelector AimActorKey;

};
