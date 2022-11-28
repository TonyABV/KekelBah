// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "KBProjectileBase.generated.h"

class SphereComponent;
class UProjectileMovementComponent;

UCLASS()
class KEKELBAH_API AKBProjectileBase : public AActor
{
	GENERATED_BODY()

private:
    FVector ShotDirection;

public:	
	AKBProjectileBase();

	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
    USphereComponent* CollisionComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
    UProjectileMovementComponent* MovementComponent;

    void SetShotDirection(const FVector& Direction) { ShotDirection = Direction; }

protected:
	virtual void BeginPlay() override;

public:	

};
