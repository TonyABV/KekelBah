// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/KBLauncherWeaponActor.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon/KBProjectileBase.h"

void AKBLauncherWeaponActor::StartFire()
{
    MakeShot();
}

void AKBLauncherWeaponActor::MakeShot()
{
    if (IsAmmoEmpty())
    {
        EndFire();
        return;
    }

    if (!GetWorld()) return;

    FVector TraceStart, TraceEnd;
    if (!GetTraceData(TraceStart, TraceEnd)) return;

    FHitResult HitResult;
    FCollisionQueryParams TraceParams;
    TraceParams.AddIgnoredActor(GetOwner());
    GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECC_Visibility, TraceParams);

    const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
    const FVector Direction = (EndPoint - WeaponMesh->GetSocketLocation(MuzzleSocketName)).GetSafeNormal();
    //const FVector Direction =  WeaponMesh->GetSocketRotation(MuzzleSocketName).Vector();
   
    const FTransform SpawnTransform(FRotator::ZeroRotator, WeaponMesh->GetSocketTransform(MuzzleSocketName).GetLocation());
    
    AKBProjectileBase* Projectile = GetWorld()->SpawnActorDeferred<AKBProjectileBase>(ProjectileClass, SpawnTransform);
    if (Projectile)
    {
        Projectile->SetShotDirection(Direction);
        Projectile->FinishSpawning(SpawnTransform);
        Projectile->SetOwner(GetOwner());
    }

    DecreaseAmmo();
    SpawnMuzzleFX();
}
