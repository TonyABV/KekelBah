// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/KBBaseCharacter.h"
#include "KBAIBaseCharacter.generated.h"

class UBehaviorTree;


UCLASS()
class KEKELBAH_API AKBAIBaseCharacter : public AKBBaseCharacter
{
	GENERATED_BODY()

public:

    AKBAIBaseCharacter(const FObjectInitializer& ObjectInitializer);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    UBehaviorTree* BehaviorTreeAsset;

protected:

	virtual void OnDeath() override;
};
