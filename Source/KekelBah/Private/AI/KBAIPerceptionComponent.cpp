// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/KBAIPerceptionComponent.h"
#include "Perception/AISense_Sight.h"
#include "Components/KBHealthComponent.h"
#include "KBUtils.h"

AActor* UKBAIPerceptionComponent::GetClosestEnemy() const
{
    TArray<AActor*> Actors;

    GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), Actors);
    if (Actors.Num() == 0) return nullptr;

    AController* Controller = GetOwner<AController>();
    if (!Controller) return nullptr;

    APawn* Pawn = Controller->GetPawn();
    if (!Pawn) return nullptr;

    FVector PawnLocation = Pawn->GetActorLocation();

    float ClosestDistance = MAX_FLT;

    AActor* ClosestActor = nullptr;

    for (const auto Actor : Actors)
    {
        if (!Actor) continue;
        FVector ActorLocation = Actor->GetActorLocation();

        UKBHealthComponent* HealthComponent = KBUtils::GetPlayerComponent<UKBHealthComponent>(Actor);

        if (!HealthComponent || HealthComponent->IsDeath()) continue; // todo: check is enemy or not

        float Distance = FVector::Dist(PawnLocation, ActorLocation);
        if(ClosestDistance > Distance)
        {
            ClosestDistance = Distance;
            ClosestActor = Actor;
        }
    }
    
    return ClosestActor;
}
