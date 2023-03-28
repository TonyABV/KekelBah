// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/KBAIController.h"
#include "AI/KBAIBaseCharacter.h"
#include "AI/KBAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "KBRespawnComponent.h"

AKBAIController::AKBAIController(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
    KBPerceptionComponent = CreateDefaultSubobject<UKBAIPerceptionComponent>("PerceptionComponent");

    SetPerceptionComponent(*KBPerceptionComponent);

    bWantsPlayerState = true;
        
    RespawnComponent = CreateDefaultSubobject<UKBRespawnComponent>("RespawnComponent");
}

void AKBAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    AKBAIBaseCharacter* AIChar = Cast<AKBAIBaseCharacter>(InPawn);
    if (AIChar)
    {
        RunBehaviorTree(AIChar->BehaviorTreeAsset);
    }
}

void AKBAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    SetFocus(GetFocusOnActor());
}

AActor* AKBAIController::GetFocusOnActor() const
{
    if (!GetBlackboardComponent()) return nullptr;

    return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(EnemyKeyName));
}

