// Fill out your copyright notice in the Description page of Project Settings.


#include "KBBaseWeaponActor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"

DEFINE_LOG_CATEGORY_STATIC(BaseWeaponLog, All, All);

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

    CurrentAmmo = DefaultAmmo;
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

AController* AKBBaseWeaponActor::GetOwnersController() const
{
    if (!GetWorld()) return nullptr;

    ACharacter* Player = GetOwner<ACharacter>();
    if (!IsValid(Player)) return nullptr;

    return Player->GetController();
}

void AKBBaseWeaponActor::DecreaseAmmo()
{
    --CurrentAmmo.Bullets;
    LogAmmo();
    if (IsClipEmpty())
    {
        OnClipEmpty.Broadcast();
    }
}

bool AKBBaseWeaponActor::IsAmmoEmpty() const
{
    return IsClipEmpty() && CurrentAmmo.Clips == 0 && !CurrentAmmo.bInfinityAmmo;
}

bool AKBBaseWeaponActor::IsClipEmpty() const
{
    return CurrentAmmo.Bullets == 0;
}

void AKBBaseWeaponActor::ChangeClip()
{
    if (!CurrentAmmo.bInfinityAmmo)
    {
        --CurrentAmmo.Clips;
    }

    CurrentAmmo.Bullets = DefaultAmmo.Bullets;
    UE_LOG(BaseWeaponLog, Display, TEXT("-----CLIP CHANGED-----"));
}

bool AKBBaseWeaponActor::CanChangeClip() const
{
    return CurrentAmmo.Bullets < DefaultAmmo.Bullets && CurrentAmmo.Clips > 0;
}

void AKBBaseWeaponActor::LogAmmo() const
{
    FString AmmoInfo = "Ammo: " + FString::FromInt(CurrentAmmo.Bullets) + " / ";
    AmmoInfo += CurrentAmmo.bInfinityAmmo ? "Infinite" : FString::FromInt(CurrentAmmo.Clips);
    UE_LOG(BaseWeaponLog, Display, TEXT("%s"), *AmmoInfo);
}

bool AKBBaseWeaponActor::GetViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const
{
    AController* PC = GetOwnersController();
    if (!IsValid(PC)) return false;
    PC->GetPlayerViewPoint(ViewLocation, ViewRotation);
    return true;
}

bool AKBBaseWeaponActor::GetTraceData(FVector& Start, FVector& End) const
{
    FVector ViewLocation;
    FRotator ViewRotation;
    if(!GetViewPoint(ViewLocation, ViewRotation)) return false;
    Start = ViewLocation;
    End = Start + ViewRotation.Vector() * TraceDistance;
    return true;
}

void AKBBaseWeaponActor::GetStartEndPoints(FVector& StartPoint, FVector& EndPoint)
{
}

