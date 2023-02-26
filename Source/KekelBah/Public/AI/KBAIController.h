// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "KBAIController.generated.h"


class UKBAIPerceptionComponent;


UCLASS()
class KEKELBAH_API AKBAIController : public AAIController
{
	GENERATED_BODY()


public:

	AKBAIController(const FObjectInitializer& ObjectInitializer);

	virtual void OnPossess(APawn* InPawn) override;

	virtual void Tick(float DeltaSeconds) override;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UKBAIPerceptionComponent* KBPerceptionComponent;
		
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "AI")
    FName EnemyKeyName = "EnemyActor";

protected:

	AActor* GetFocusOnActor() const;
};
