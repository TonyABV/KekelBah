// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "KBWeaponComponent.generated.h"

class AKBBaseWeaponActor;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KEKELBAH_API UKBWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UKBWeaponComponent();

    void StartFire();
    void EndFire();

    void NextWeapon();

protected:

	virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    void SpawnWeapons();

    void AttachWeaponToMesh(AKBBaseWeaponActor* Weapon, USkeletalMeshComponent* SkeletalMesh, const FName& SocketName);

    void EquipWeapon(int32 WeaponIndex);

protected:

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TArray<TSubclassOf<AKBBaseWeaponActor>> WeaponClasses;

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponEquipPointName = "WeaponPoint";

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponArmoryPointName = "ArmorySocket";

    UPROPERTY()
    AKBBaseWeaponActor* CurrentWeapon = nullptr;

    UPROPERTY()
    TArray<AKBBaseWeaponActor*> Weapons;

    int32 CurrentWeaponIndex = 0.f;

public:	


};
