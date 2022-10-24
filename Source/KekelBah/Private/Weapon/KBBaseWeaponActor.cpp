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

void AKBBaseWeaponActor::Fire()
{
    UE_LOG(BaseWeapon, Display, TEXT("Fire!"));

	MakeShot();
}


void AKBBaseWeaponActor::MakeShot()
{
    if (!GetWorld()) return;

	ACharacter* Player = GetOwner<ACharacter>();
    if (!IsValid(Player)) return;

	AController* OwnersController = Player->GetController();
    if (!IsValid(OwnersController)) return;

	FVector ViewLocation;
    FRotator ViewRotation;
	OwnersController->GetPlayerViewPoint(ViewLocation, ViewRotation);

	FTransform MuzzleTransform = WeaponMesh->GetSocketTransform(MuzzleSocketName);

    FVector StartPoint = ViewLocation;               //MuzzleTransform.GetLocation();
    FVector ShootDirection = ViewRotation.Vector();  // MuzzleTransform.GetRotation().GetForwardVector();
    FVector EndPoint = ViewLocation + ShootDirection * TraceDistance;


	FHitResult HitResult;
    FCollisionQueryParams TraceParams;
    TraceParams.AddIgnoredActor(GetOwner());
    GetWorld()->LineTraceSingleByChannel(HitResult, StartPoint, EndPoint, ECC_Visibility, TraceParams);

	if (HitResult.bBlockingHit)
	{
        DrawDebugLine(GetWorld(), MuzzleTransform.GetLocation(), HitResult.ImpactPoint, FColor::Orange, false, 1.f);
        DrawDebugSphere(GetWorld(), HitResult.ImpactPoint, 10.f, 15.f, FColor::Red, false, 5.f);
        
        if (!IsValid(HitResult.GetActor())) return;

        HitResult.GetActor()->TakeDamage(Damage, {}, OwnersController, this);
       //UE_LOG(BaseWeapon, Display, TEXT("Hited bone : %s"), *HitResult.BoneName.ToString());
	}
    else
    {
        DrawDebugLine(GetWorld(), MuzzleTransform.GetLocation(), EndPoint, FColor::Orange, false, 1.f);
    }

}

