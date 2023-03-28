#pragma once

#include "CoreMinimal.h"
#include "KBCoreTypes.generated.h"

// VFX

class UNiagaraSystem;

USTRUCT(BlueprintType)
struct FDecalData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    UMaterialInstance* DecalMaterial;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    FVector Size = FVector(10.f);

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    float LifeTime = 0.7f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    float FadeOutTime = 0.7f;

};

USTRUCT(BlueprintType)
struct FImpactData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    UNiagaraSystem* NiagaraEffect;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    FDecalData DecalData;
};

USTRUCT(BlueprintType)
struct FGameData
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "1", ClampMax = "100"))
    int32 PlayersNum = 2;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "3", ClampMax = "10"))
    int32 RoundNum = 3;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "3", ClampMax = "300"))
    int32 RoundTime = 3;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
    FLinearColor DefaultTeamColor = FLinearColor::Red;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game")
    TArray<FLinearColor> TeamColors;
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Game", meta = (ClampMin = "1", ClampMax = "20"))
    int32 RespawnTime = 5;
};