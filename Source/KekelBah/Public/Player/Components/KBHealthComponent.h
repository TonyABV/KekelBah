// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "KBHealthComponent.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnDeath);

DECLARE_MULTICAST_DELEGATE(FOnDamaged);

DECLARE_MULTICAST_DELEGATE(FOnFullHealth);

DECLARE_MULTICAST_DELEGATE_OneParam(FOnHealthChanged, const float);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KEKELBAH_API UKBHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UKBHealthComponent();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (ClampMin = "1", ClampMax = "500"))
    float MaxHealth = 100.f;

	UFUNCTION(BlueprintCallable)
    float GetCurrentHealth() const { return Health; }

	UFUNCTION(BlueprintCallable)
    bool IsDeath();

    FOnDeath OnDead;

	FOnHealthChanged OnHealthChanged;

    FOnDamaged OnDamaged;

    FOnFullHealth OnFullHealth;

	UPROPERTY(EditDefaultsOnly, Category = "AutoHeal")
    bool bAutoHealEnable = false;

	UPROPERTY(EditDefaultsOnly, Category = "AutoHeal", meta = (EditCondition = "bAutoHealEnable"))
    float AutoHealDelay = 0.5f;

	UPROPERTY(EditDefaultsOnly, Category = "AutoHeal", meta = (EditCondition = "bAutoHealEnable"))
    float AutoHealSpan = 0.2f;

    UPROPERTY(EditDefaultsOnly, Category = "AutoHeal", meta = (EditCondition = "bAutoHealEnable"))
    float AutoHealValue = 1.f;

	UFUNCTION()
    void TryOnAutoHeal();

	UFUNCTION(BlueprintCallable)
	float GetHealthPercent() const;

protected:

	virtual void BeginPlay() override;

	float Health = 0.f;

	UFUNCTION()
    void OnTakeDamageHandle(
        AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);

	FTimerHandle AutoHealHandle;
	
	UFUNCTION()
    void Heal(const float Value);

	UFUNCTION()
    void StopAutoHeal();
};
