// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/KBProjectileBase.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AKBProjectileBase::AKBProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    CollisionComponent->SetSphereRadius(5.f);
    SetRootComponent(CollisionComponent);

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");
    MovementComponent->InitialSpeed = 1000.f;
    MovementComponent->ProjectileGravityScale = 0.f;
}

// Called when the game starts or when spawned
void AKBProjectileBase::BeginPlay()
{
	Super::BeginPlay();

    MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;

    SetLifeSpan(5.f);
}

