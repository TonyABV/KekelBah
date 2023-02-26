// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/EQS/EnvQueryTest_WeaponPickupType.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_ActorBase.h"
#include "Pickups/KBAmmoPickup.h"
#include "KBBaseWeaponActor.h"

UEnvQueryTest_WeaponPickupType::UEnvQueryTest_WeaponPickupType()
{
    Cost = EEnvTestCost::Low;
    ValidItemType = UEnvQueryItemType_ActorBase::StaticClass();
    SetWorkOnFloatValues(false);
}

void UEnvQueryTest_WeaponPickupType::RunTest(FEnvQueryInstance& QueryInstance) const
{
    UObject* DataOwner = QueryInstance.Owner.Get();
    BoolValue.BindData(DataOwner, QueryInstance.QueryID);
    bool bWantsBeTakable = BoolValue.GetValue();

    for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
    {
        const auto ItemActor = Cast<AKBAmmoPickup>(GetItemActor(QueryInstance, It.GetIndex()));

        if (!ItemActor) continue;

        bool ShouldBeTaken = ItemActor->GetWeaponType() == WeaponType;

        It.SetScore(TestPurpose, FilterType, ShouldBeTaken, bWantsBeTakable);
    }
}
