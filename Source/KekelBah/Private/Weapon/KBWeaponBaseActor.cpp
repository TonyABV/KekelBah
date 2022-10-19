// Fill out your copyright notice in the Description page of Project Settings.


#include "KBWeaponBaseActor.h"
#include "Components/SkeletalMeshComponent.h"


AKBWeaponBaseActor::AKBWeaponBaseActor()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
    SetRootComponent(WeaponMesh);
}

void AKBWeaponBaseActor::BeginPlay()
{
	Super::BeginPlay();
}
