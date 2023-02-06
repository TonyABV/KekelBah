// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/KBWeaponFXComponent.h"
#include "NiagaraFunctionLibrary.h"


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
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), ImpactEffect, HitResult.ImpactPoint, HitResult.Normal.Rotation());
}

