// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon/KBProjectileBase.h"
#include "KBProjectileTest.generated.h"

/**
 * 
 */
UCLASS()
class KEKELBAH_API AKBProjectileTest : public AKBProjectileBase
{
	GENERATED_BODY()
		
    virtual void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
        FVector NormalImpulse, const FHitResult& Hit) override;
	
};
