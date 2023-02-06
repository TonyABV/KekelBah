// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SphereComponent.h"
#include "GameFramework/Actor.h"
#include "KBProjectileBase.generated.h"

class SphereComponent;
class UProjectileMovementComponent;
class UKBWeaponFXComponent;

UCLASS()
class KEKELBAH_API AKBProjectileBase : public AActor
{
	GENERATED_BODY()
		
public:	
	AKBProjectileBase();

	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
    USphereComponent* CollisionComponent;

	UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
    UProjectileMovementComponent* MovementComponent;
	
    UPROPERTY(EditAnywhere, Category = "FXComponent")
    UKBWeaponFXComponent* FXComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float DamageRadius = 200.f;

    UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float DamageAmount = 50.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
    bool bFullDamage = true;

public:
    void SetShotDirection(const FVector& Direction) { ShotDirection = Direction; }

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent*
        OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	AController* GetOwnersController();

private:
    FVector ShotDirection;

};
