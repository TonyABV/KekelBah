// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EQS/EnvQueryTest_CouldBeTaken.h"

#include "EnvironmentQuery/Items/EnvQueryItemType_ActorBase.h"
#include "Pickups/KBBasePickup.h"

UEnvQueryTest_CouldBeTaken::UEnvQueryTest_CouldBeTaken()
{
    Cost = EEnvTestCost::Low;
    ValidItemType = UEnvQueryItemType_ActorBase::StaticClass();
    SetWorkOnFloatValues(false);
}

void UEnvQueryTest_CouldBeTaken::RunTest(FEnvQueryInstance& QueryInstance) const
{
    UObject* DataOwner = QueryInstance.Owner.Get();
    BoolValue.BindData(DataOwner, QueryInstance.QueryID);
    bool bWantsBeTakable = BoolValue.GetValue();

    for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
    {
        const auto ItemActor = Cast<AKBBasePickup>(GetItemActor(QueryInstance, It.GetIndex()));

        if (!ItemActor) continue;

        bool ShouldBeTaken = ItemActor->CanBeTaken();
        
        It.SetScore(TestPurpose, FilterType, ShouldBeTaken, bWantsBeTakable);
    }
}
