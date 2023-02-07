// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/KBRifleWeaponActor.h"
#include "DrawDebugHelpers.h"
#include "KBWeaponFXComponent.h"
#include "KBWeaponFXComponent.h"


AKBRifleWeaponActor::AKBRifleWeaponActor()
{
    FXComponent = CreateDefaultSubobject<UKBWeaponFXComponent>("FXComponent");
}

void AKBRifleWeaponActor::StartFire()
{
    GetWorld()->GetTimerManager().SetTimer(FireHandle, this, &AKBRifleWeaponActor::MakeShot, TimeBetweenShots, true);
}

void AKBRifleWeaponActor::EndFire()
{
    GetWorld()->GetTimerManager().ClearTimer(FireHandle);
}

void AKBRifleWeaponActor::BeginPlay()
{
    Super::BeginPlay();

    check(FXComponent);
}

void AKBRifleWeaponActor::MakeShot()
{
    if (IsAmmoEmpty())
    {
        EndFire();
        return;
    }

    if (!GetOwnersController()) EndFire();


    FVector StartPoint;
    FVector EndPoint;
    GetStartEndPoints(StartPoint, EndPoint);

    FHitResult HitResult;
    FCollisionQueryParams TraceParams;
    TraceParams.AddIgnoredActor(GetOwner());
    TraceParams.bReturnPhysicalMaterial = true;
    GetWorld()->LineTraceSingleByChannel(HitResult, StartPoint, EndPoint, ECC_Visibility, TraceParams);

    FTransform MuzzleTransform = WeaponMesh->GetSocketTransform(MuzzleSocketName);

    DecreaseAmmo();

    if (HitResult.bBlockingHit)
    {
        if (!IsValid(HitResult.GetActor())) return;

        HitResult.GetActor()->TakeDamage(Damage, {}, GetOwnersController(), this);

        FXComponent->PlayImpactFX(HitResult);
    }
    else
    {
        DrawDebugLine(GetWorld(), MuzzleTransform.GetLocation(), EndPoint, FColor::Orange, false, 1.f);
    }

}

void AKBRifleWeaponActor::GetStartEndPoints(FVector& StartPoint, FVector& EndPoint)
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
    EndPoint = ViewLocation + FMath::VRandCone(ShootDirection, HalfAngleRad) * TraceDistance;
}
