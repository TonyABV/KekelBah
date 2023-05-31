// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon/KBWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
#include "Kismet/GameplayStatics.h"
#include "Components/DecalComponent.h"
#include "Sound/SoundCue.h"

UKBWeaponFXComponent::UKBWeaponFXComponent()
{
    PrimaryComponentTick.bCanEverTick = false;
}

void UKBWeaponFXComponent::BeginPlay()
{
    Super::BeginPlay();
}

void UKBWeaponFXComponent::PlayImpactFX(const FHitResult& HitResult)
{
    auto Effect = DefaultImpactData;

    if (HitResult.PhysMaterial.IsValid())
    {
        if (Effects.Contains(HitResult.PhysMaterial.Get()))
        {
            Effect = Effects[HitResult.PhysMaterial.Get()];
        }
    }

    //Niagara
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),  //
        Effect.NiagaraEffect,                                   //
        HitResult.ImpactPoint,                                  //
        HitResult.Normal.Rotation());

    //Decal
    auto DecalComponent = UGameplayStatics::SpawnDecalAtLocation(GetWorld(),  //
        Effect.DecalData.DecalMaterial,                                       //
        Effect.DecalData.Size,                                                //
        HitResult.ImpactPoint,                                                //
        HitResult.Normal.Rotation());

    if (DecalComponent)
    {
        DecalComponent->SetFadeOut(Effect.DecalData.LifeTime, Effect.DecalData.FadeOutTime);
    }

    //Sound
    UGameplayStatics::SpawnSoundAtLocation(GetWorld(), Effect.HitSound, HitResult.ImpactPoint);
}
