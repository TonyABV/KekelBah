// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/KBAIBaseCharacter.h"
#include "AI/KBAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "KBAIWeaponComponent.h"
#include "BrainComponent.h"

AKBAIBaseCharacter::AKBAIBaseCharacter(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<UKBAIWeaponComponent>("WeaponComponent"))
{
    AutoPossessAI = EAutoPossessAI::Disabled;
    AIControllerClass = AKBAIController::StaticClass();

    bUseControllerRotationYaw = false;
    if (GetCharacterMovement())
    {
        GetCharacterMovement()->bUseControllerDesiredRotation = true;
        GetCharacterMovement()->RotationRate = FRotator(0.f, 200.f, 0.f);
    }
}

void AKBAIBaseCharacter::OnDeath()
{
    const auto AIController = Cast<AAIController>(Controller);

    if (AIController && AIController->BrainComponent)
    {
        AIController->BrainComponent->Cleanup();
    }

    Super::OnDeath();
}
