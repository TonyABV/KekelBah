// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KBBaseWeaponActor.generated.h"

class USkeletalMeshComponent;

UCLASS()
class KEKELBAH_API AKBBaseWeaponActor : public AActor
{
	GENERATED_BODY()
	
public:	

	AKBBaseWeaponActor();

	virtual void StartFire();
    virtual void EndFire();

protected:


	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USkeletalMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Fire")
    FName MuzzleSocketName = "MuzzleSocket";

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Fire")
    float TraceDistance = 1500.f;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Fire")
    float Damage = 10.f;

protected:

	virtual void BeginPlay() override;

	virtual  void MakeShot();

    virtual void GetStartEndPoints(FVector& StartPoint, FVector& EndPoint);

    AController* GetOwnersController() const;


public:
    bool GetViewPoint(FVector& ViewLocation, FRotator& ViewRotation) const;

    bool GetTraceData(FVector& Start, FVector& End) const;
};
