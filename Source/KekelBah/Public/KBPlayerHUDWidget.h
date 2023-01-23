// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Weapon/KBBaseWeaponActor.h"
#include "KBPlayerHUDWidget.generated.h"


class UKBWeaponComponent;
class UKBHealthComponent;

UCLASS()
class KEKELBAH_API UKBPlayerHUDWidget : public UUserWidget
{
    GENERATED_BODY()

protected:

    UPROPERTY()
    UKBWeaponComponent* WeaponComponent;

    UPROPERTY()
    UKBHealthComponent* HealthComponent;
    
public:

    UFUNCTION(BlueprintCallable, Category = "UI")
    float GetHealthPercent();

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetUIWeaponData(FUIWeaponData& UIWeaponData);

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetWeaponAmmoData(FWeaponAmmo& WeaponAmmoData);

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool IsPlayerAlive();   
    
    UFUNCTION(BlueprintCallable, Category = "UI")
    bool IsPlayerSpectating();
    
private:

    bool InitWeaponComponent();

    bool InitHealthComponent();
    
};