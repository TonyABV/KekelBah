// Fill out your copyright notice in the Description page of Project Settings.


#include "KBBaseWeaponActor.h"
#include "Components/SkeletalMeshComponent.h"

DEFINE_LOG_CATEGORY_STATIC(BaseWeapon, All, All);

AKBBaseWeaponActor::AKBBaseWeaponActor()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
    SetRootComponent(WeaponMesh);
}

void AKBBaseWeaponActor::Fire()
{
    UE_LOG(BaseWeapon, Display, TEXT("Fire!"));
}

void AKBBaseWeaponActor::BeginPlay()
{
	Super::BeginPlay();
}
