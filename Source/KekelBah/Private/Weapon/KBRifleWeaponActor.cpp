// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/KBRifleWeaponActor.h"
#include "DrawDebugHelpers.h"
#include "KBWeaponFXComponent.h"
#include "KBWeaponFXComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"


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
    SetMuzzleFXVisibility(false);
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
        
    if (HitResult.bBlockingHit)
    {
        EndPoint = HitResult.ImpactPoint;
        if (!IsValid(HitResult.GetActor())) return;

        HitResult.GetActor()->TakeDamage(Damage, {}, GetOwnersController(), this);

        FXComponent->PlayImpactFX(HitResult);
    }

    FTransform MuzzleTransform = WeaponMesh->GetSocketTransform(MuzzleSocketName);
    SpawnTraceFX(MuzzleTransform.GetLocation(), EndPoint);
    InitMuzzleFX();

    DecreaseAmmo();
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

void AKBRifleWeaponActor::InitMuzzleFX()
{
    if (IsAmmoEmpty()) return;

    if (!MuzzleFXComponent)
    {
        MuzzleFXComponent = SpawnMuzzleFX();
    }
    SetMuzzleFXVisibility(true);
}

void AKBRifleWeaponActor::SetMuzzleFXVisibility(bool IsVisible)
{
    if (!MuzzleFXComponent) return;

    MuzzleFXComponent->SetPaused(!IsVisible);
    MuzzleFXComponent->SetVisibility(IsVisible);
}

void AKBRifleWeaponActor::SpawnTraceFX(FVector StartPoint, FVector EndPoint)
{
    const auto TraceFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TraceFX, StartPoint);

    if (TraceFXComponent)
    {
        TraceFXComponent->SetNiagaraVariableVec3("EndLocation", EndPoint);
    }
}
