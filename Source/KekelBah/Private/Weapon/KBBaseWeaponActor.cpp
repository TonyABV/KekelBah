// Fill out your copyright notice in the Description page of Project Settings.


#include "KBBaseWeaponActor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"

DEFINE_LOG_CATEGORY_STATIC(BaseWeapon, All, All);

AKBBaseWeaponActor::AKBBaseWeaponActor()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>("WeaponMesh");
    SetRootComponent(WeaponMesh);
}

void AKBBaseWeaponActor::BeginPlay()
{
	Super::BeginPlay();

	check(WeaponMesh);
}

void AKBBaseWeaponActor::StartFire()
{
}

void AKBBaseWeaponActor::EndFire()
{
}


void AKBBaseWeaponActor::MakeShot()
{
}

AController* AKBBaseWeaponActor::GetOwnersController()
{
    if (!GetWorld()) return nullptr;

    ACharacter* Player = GetOwner<ACharacter>();
    if (!IsValid(Player)) return nullptr;

    return Player->GetController();
}

void AKBBaseWeaponActor::GetStartEndPoints(FVector& StartPoint, FVector& EndPoint)
{
}

