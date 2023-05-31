// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KBBaseWeaponActor.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnClipEmpty, AKBBaseWeaponActor*);

class USkeletalMeshComponent;
class UNiagaraSystem;
class UNiagaraComponent;
class USoundCue;

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

    bool IsAmmoFull() const;

    FOnClipEmpty OnClipEmpty;

    FUIWeaponData GetUIWeaponData() const { return UIWeaponData; }

    FWeaponAmmo GetCurrentAmmoData() const { return CurrentAmmo; }

    bool TryAddAmmo(int32 ClipAmount);

    bool IsAmmoEmpty() const;

    bool IsClipEmpty() const;

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire")
    FName MuzzleSocketName = "MuzzleSocket";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire")
    float TraceDistance = 1500.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Fire")
    float Damage = 10.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Ammo")
    FWeaponAmmo DefaultAmmo{10, 5, false};

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    FUIWeaponData UIWeaponData;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    UNiagaraSystem* MuzzleFX;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
    USoundCue* FireSound = nullptr;

private:

    FWeaponAmmo CurrentAmmo;

protected:

	virtual void BeginPlay() override;

	virtual  void MakeShot();

    virtual void GetStartEndPoints(FVector& StartPoint, FVector& EndPoint);

    AController* GetOwnersController() const;

    void DecreaseAmmo();
    
    void LogAmmo() const;

    UNiagaraComponent* SpawnMuzzleFX() const;
};
