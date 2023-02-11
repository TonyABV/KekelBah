// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/KBAIBaseCharacter.h"
#include "AI/KBAIController.h"

AKBAIBaseCharacter::AKBAIBaseCharacter(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer)
{
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    AIControllerClass = AKBAIController::StaticClass();
}
