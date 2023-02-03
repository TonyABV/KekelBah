// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickups/KBBasePickup.h"
#include "Components/SphereComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogBasePickup, All, All)

AKBBasePickup::AKBBasePickup()
{
	PrimaryActorTick.bCanEverTick = true;
	
	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    CollisionComponent->SetSphereRadius(30.f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    SetRootComponent(CollisionComponent);
}


void AKBBasePickup::BeginPlay()
{
    Super::BeginPlay();
    GenerateRandomYawRotation();
}

void AKBBasePickup::NotifyActorBeginOverlap(AActor* OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

    APawn* PlayerPawn = Cast<APawn>(OtherActor);
    if (IsValid(PlayerPawn) && GivePickupTo(PlayerPawn))
    {
        PickupWasTaken();
	    UE_LOG(LogBasePickup, Display, TEXT("%s overlap"), *(OtherActor->GetName()));
    }
}

void AKBBasePickup::PickupWasTaken()
{
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    GetRootComponent()->SetVisibility(false, true);

    FTimerHandle RespawnHandle;
    GetWorld()->GetTimerManager().SetTimer(RespawnHandle, this, &AKBBasePickup::RespawnPickup, RespawnTime);
}

void AKBBasePickup::RespawnPickup()
{
    GetRootComponent()->SetVisibility(true, true);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    GenerateRandomYawRotation();
}

bool AKBBasePickup::GivePickupTo(APawn* PlayerPawn)
{
    return false;
}

void AKBBasePickup::GenerateRandomYawRotation()
{
    const auto Direction = FMath::RandBool() ? 1.f : -1.f;
    YawRotation = FMath::FRandRange(1.f, 5.f) * Direction;
}


void AKBBasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    AddActorLocalRotation(FRotator(0., YawRotation, 0.f));

    float LifeTime = GetGameTimeSinceCreation();
    
    float Multiplier = FMath::Sin(LifeTime) * 200.f * DeltaTime;

    AddActorLocalOffset(FVector(0.f, 0.f, Multiplier));
}

