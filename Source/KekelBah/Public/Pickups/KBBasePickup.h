// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KBBasePickup.generated.h"

class USphereComponent;

UCLASS()
class KEKELBAH_API AKBBasePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKBBasePickup();

protected:

    UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
    USphereComponent* CollisionComponent;

	UPROPERTY(EditAnywhere)
    float RespawnTime = 5.f;

		
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

	void PickupWasTaken();

	void RespawnPickup();

private:

	virtual bool GivePickupTo(APawn* Pawn);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};