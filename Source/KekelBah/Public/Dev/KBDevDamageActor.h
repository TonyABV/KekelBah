// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KBDevDamageActor.generated.h"

UCLASS()
class KEKELBAH_API AKBDevDamageActor : public AActor
{
    GENERATED_BODY()

    USceneComponent* SceneComponent;

public:	
	// Sets default values for this actor's properties
	AKBDevDamageActor();

	UPROPERTY(EditAnywhere, meta = (ClampMin = "0."))
    float SphereRadius = 0.f;

	UPROPERTY(EditAnywhere)
    TSubclassOf<UDamageType> DamageType;

	UPROPERTY(EditAnywhere)
    FColor Color = FColor::Cyan;

	UPROPERTY(EditAnywhere)
    float Damage = 0.f;

	UPROPERTY(EditAnywhere)
    float DamageSpan = 1.f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
    void ApplyDamage();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
