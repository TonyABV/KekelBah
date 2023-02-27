// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/KBBaseWeaponActor.h"
#include "KBRifleWeaponActor.generated.h"

class UKBWeaponFXComponent;
class UNiagaraComponent;
class UNiagaraSystem;

UCLASS()
class KEKELBAH_API AKBRifleWeaponActor : public AKBBaseWeaponActor
{
	GENERATED_BODY()

public:

    AKBRifleWeaponActor();

    virtual void StartFire() override;
    virtual void EndFire() override;

protected:

    UPROPERTY(EditAnywhere, Category = "FXComponent")
    UKBWeaponFXComponent* FXComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Fire")
    float TimeBetweenShots = 0.2f;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Fire")
    float FireSpreadAngle = 3.f;

    FTimerHandle FireHandle;

    UPROPERTY()
    UNiagaraComponent* MuzzleFXComponent;
    
    UPROPERTY(EditDefaultsOnly, Category = "VFX")
    UNiagaraSystem* TraceFX;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    FString TraceTargetName = "TraceTarget";

protected:

    virtual void BeginPlay() override;

    virtual void MakeShot() override;

    virtual  void GetStartEndPoints(FVector& StartPoint, FVector& EndPoint) override;

    void InitMuzzleFX();

    void SetMuzzleFXVisibility(bool IsVisible);

    void SpawnTraceFX(FVector StartPoint, FVector EndPoint);
};
