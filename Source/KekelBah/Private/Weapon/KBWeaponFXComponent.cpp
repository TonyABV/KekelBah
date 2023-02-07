// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/KBWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"


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
    auto Effect = DefaultEffect;

	if(HitResult.PhysMaterial.IsValid())
	{
        if (Effects.Contains(HitResult.PhysMaterial.Get()))
        {
            Effect = Effects[HitResult.PhysMaterial.Get()];
        }
	}

    UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Effect, HitResult.ImpactPoint, HitResult.Normal.Rotation());
}

