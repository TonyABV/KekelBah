// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "KBWeaponFXComponent.generated.h"

class UNiagaraSystem;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KEKELBAH_API UKBWeaponFXComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UKBWeaponFXComponent();

    void PlayImpactFX(const FHitResult& HitResult);

protected:

	UPROPERTY(EditDefaultsOnly, Category = "VFX")
    UNiagaraSystem* ImpactEffect;

protected:

	virtual void BeginPlay() override;

			
};
