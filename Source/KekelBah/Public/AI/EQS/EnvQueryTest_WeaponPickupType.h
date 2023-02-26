// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EnvQueryTest_WeaponPickupType.generated.h"

class AKBBaseWeaponActor;

UCLASS()
class KEKELBAH_API UEnvQueryTest_WeaponPickupType : public UEnvQueryTest
{
	GENERATED_BODY()

public:

    UEnvQueryTest_WeaponPickupType();

    virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    TSubclassOf<AKBBaseWeaponActor> WeaponType;

};
