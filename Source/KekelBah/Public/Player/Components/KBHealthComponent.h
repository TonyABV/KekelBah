// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "KBHealthComponent.generated.h"


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

protected:

	virtual void BeginPlay() override;

	float Health = 0.f;

	UFUNCTION()
    void OnTakeDamageHandle(
        AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);
};
