// Fill out your copyright notice in the Description page of Project Settings.


#include "Dev/KBDevDamageActor.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AKBDevDamageActor::AKBDevDamageActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
    SetRootComponent(SceneComponent);
	
}

// Called when the game starts or when spawned
void AKBDevDamageActor::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle DamageHandle;
    GetWorld()->GetTimerManager().SetTimer(
        DamageHandle,
        [=]()
        {
            UGameplayStatics::ApplyRadialDamage(
                GetWorld(), Damage, GetActorLocation(), SphereRadius, DamageType, {}, this, GetInstigatorController(), true);
        },
        DamageSpan, true, DamageSpan);
}

// Called every frame
void AKBDevDamageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	DrawDebugSphere(GetWorld(), GetActorLocation(), SphereRadius, 16, Color);
}

