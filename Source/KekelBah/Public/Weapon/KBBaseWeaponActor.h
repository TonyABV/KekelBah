// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KBBaseWeaponActor.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnClipEmpty);

class USkeletalMeshComponent;

USTRUCT(BlueprintType)
struct FWeaponAmmo
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    int32 Bullets;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (EditCondition = "!bInfinityAmmo"))
    int32 Clips;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    bool bInfinityAmmo;
    
};

USTRUCT(BlueprintType)
struct FUIWeaponData
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    UTexture2D* CrossHairIcon;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    UTexture2D* WeaponIcon;
};

UCLASS()
class KEKELBAH_API AKBBaseWeaponActor : public AActor
{
	GENERATED_BODY()
	
public:	

	AKBBaseWeaponActor();

	virtual void StartFire();
    virtual void EndFire();

    bool GetViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;

    bool GetTraceData(FVector& Start, FVector& End) const;

    void ChangeClip();

    bool CanChangeClip() const;

    FOnClipEmpty OnClipEmpty;

    FUIWeaponData GetUIWeaponData() const { return UIWeaponData; }

    FWeaponAmmo GetCurrentAmmoData() const { return CurrentAmmo; }

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Fire")
    FName MuzzleSocketName = "MuzzleSocket";

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Fire")
    float TraceDistance = 1500.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Fire")
    float Damage = 10.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo")
    FWeaponAmmo DefaultAmmo{10, 5, false};

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    FUIWeaponData UIWeaponData;

private:

    FWeaponAmmo CurrentAmmo;

protected:

	virtual void BeginPlay() override;

	virtual  void MakeShot();

    virtual void GetStartEndPoints(FVector& StartPoint, FVector& EndPoint);

    AController* GetOwnersController() const;

    void DecreaseAmmo();

    bool IsAmmoEmpty() const;

    bool IsClipEmpty() const;

    void LogAmmo() const;
};
