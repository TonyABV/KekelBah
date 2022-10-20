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

    void Fire();
protected:

	virtual void BeginPlay() override;

    void SpawnWeapon();


protected:

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TSubclassOf<AKBBaseWeaponActor> WeaponClass;

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponAttachPointName = "WeaponPoint";

    UPROPERTY()
    AKBBaseWeaponActor* CurrentWeapon = nullptr;

public:	
	
};
