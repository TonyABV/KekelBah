// Fill out your copyright notice in the Description page of Project Settings.


#include "KBBaseWeaponActor.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "Dev/KBAcidDamageType.h"

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
    UE_LOG(BaseWeapon, Display, TEXT("StartFire!"));

    GetWorld()->GetTimerManager().SetTimer(FireHandle, this, &AKBBaseWeaponActor::MakeShot, TimeBetweenShots, true);
}

void AKBBaseWeaponActor::EndFire()
{
    UE_LOG(BaseWeapon, Display, TEXT("EndFire!"));
    GetWorld()->GetTimerManager().ClearTimer(FireHandle);
}


void AKBBaseWeaponActor::MakeShot()
{
    if (!GetOwnersController()) EndFire();

    FVector StartPoint;
    FVector EndPoint;
    GetStartEndPoints(StartPoint, EndPoint);

	FHitResult HitResult;
    FCollisionQueryParams TraceParams;
    TraceParams.AddIgnoredActor(GetOwner());
    GetWorld()->LineTraceSingleByChannel(HitResult, StartPoint, EndPoint, ECC_Visibility, TraceParams);

	FTransform MuzzleTransform = WeaponMesh->GetSocketTransform(MuzzleSocketName);

	if (HitResult.bBlockingHit)
	{
        DrawDebugLine(GetWorld(), MuzzleTransform.GetLocation(), HitResult.ImpactPoint, FColor::Orange, false, 1.f);
        DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.f, 15.f, FColor::Red, false, 5.f);
        
        if (!IsValid(HitResult.GetActor())) return;

        HitResult.GetActor()->TakeDamage(Damage, {}, GetOwnersController(), this);
	}
    else
    {
        DrawDebugLine(GetWorld(), MuzzleTransform.GetLocation(), EndPoint, FColor::Orange, false, 1.f);
    }

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
    FVector ViewLocation;
    FRotator ViewRotation;
    AController* PC = GetOwnersController();
    if (PC)
    {
        PC->GetPlayerViewPoint(ViewLocation, ViewRotation);
    }

    StartPoint = ViewLocation;
    FVector ShootDirection = ViewRotation.Vector();

    const float HalfAngleRad = FMath::DegreesToRadians(FireSpreadAngle / 2);
    EndPoint = ViewLocation + FMath::VRandCone(ShootDirection, HalfAngleRad)*TraceDistance;
}

