// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EQS/KBEnemyEnvQueryContext.h"
#include "EnvironmentQuery/EnvQueryTest.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_Actor.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"

void UKBEnemyEnvQueryContext::ProvideContext(FEnvQueryInstance& QueryInstance, FEnvQueryContextData& ContextData) const
{
    const auto Owner = Cast<AActor>(QueryInstance.Owner.Get());

    const auto Blackboard = UAIBlueprintHelperLibrary::GetBlackboard(Owner);

    if (!Blackboard) return;

    const auto Enemy = Cast<AActor>(Blackboard->GetValueAsObject(EnemyActorKeyName));

    UEnvQueryItemType_Actor::SetContextHelper(ContextData, Enemy);
}
