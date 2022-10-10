// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/KBBaseCharacterMovementComponent.h"
#include "Player/KBBaseCharacter.h"

float UKBBaseCharacterMovementComponent::GetMaxSpeed() const
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
