// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Weapon/KBBaseWeaponActor.h"
#include "KBCoreTypes.h"
#include "KBPlayerHUDWidget.generated.h"


class UKBWeaponComponent;
class UKBHealthComponent;
class AKBGameModeBase;
class AKBPlayerState;

UCLASS()
class KEKELBAH_API UKBPlayerHUDWidget : public UUserWidget
{
    GENERATED_BODY()

protected:

    UPROPERTY()
    UKBWeaponComponent* WeaponComponent;

    UPROPERTY()
    UKBHealthComponent* HealthComponent;

    UPROPERTY()
    AKBGameModeBase* GameMode;

    UPROPERTY()
    AKBPlayerState* PlayerState;
    
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

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetPlayerKills(int32& Kills);

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetPlayerDeaths(int32& Deaths);

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetRoundTime(int32& RoundTime);

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetCurrentRound(int32& RoundTime);

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetRoundNum(int32& RoundTime);

    virtual bool Initialize() override;
    
    UFUNCTION(BlueprintImplementableEvent)
    void OnTakeDamage();

private:
    
    bool InitWeaponComponent();

    bool InitHealthComponent();
    
};