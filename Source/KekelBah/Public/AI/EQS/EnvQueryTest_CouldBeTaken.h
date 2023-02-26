// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EnvQueryTest_CouldBeTaken.generated.h"

class AKBBasePickup;

UCLASS()
class KEKELBAH_API UEnvQueryTest_CouldBeTaken : public UEnvQueryTest
{
	GENERATED_BODY()

public:

	UEnvQueryTest_CouldBeTaken();

    virtual void RunTest(FEnvQueryInstance& QueryInstance) const override;

};
