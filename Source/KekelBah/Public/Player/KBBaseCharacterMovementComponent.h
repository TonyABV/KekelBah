// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Player/KBBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "KBBaseCharacterMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class KEKELBAH_API UKBBaseCharacterMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:

    virtual float GetMaxSpeed() const override;

    UPROPERTY()
    float SprintMultiplier = 1.5f;

    UPROPERTY()
    float SlowSteppingMultiplier = 0.5f;
};

inline float UKBBaseCharacterMovementComponent::GetMaxSpeed() const
{
    AKBBaseCharacter* Owner = Cast<AKBBaseCharacter>(GetPawnOwner());

    float DefaultMaxSpeed = Super::GetMaxSpeed();

    if (IsValid(Owner))
    {
        return Owner->IsSprinting()      ? DefaultMaxSpeed * SprintMultiplier
               : Owner->IsSlowStepping() ? DefaultMaxSpeed * SlowSteppingMultiplier
                                         : DefaultMaxSpeed;
    }
    return DefaultMaxSpeed;
}
