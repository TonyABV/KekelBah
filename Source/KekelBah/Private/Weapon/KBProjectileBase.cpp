// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon/KBProjectileBase.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "KBWeaponFXComponent.h"

// Sets default values
AKBProjectileBase::AKBProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    CollisionComponent->SetSphereRadius(5.f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    CollisionComponent->bReturnMaterialOnMove = true;
    //CollisionComponent->
    SetRootComponent(CollisionComponent);

	MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");
    MovementComponent->InitialSpeed = 1000.f;
    MovementComponent->ProjectileGravityScale = 0.f;

    FXComponent = CreateDefaultSubobject<UKBWeaponFXComponent>("FXComponent");
}

// Called when the game starts or when spawned
void AKBProjectileBase::BeginPlay()
{
	Super::BeginPlay();

    check(CollisionComponent);
    check(MovementComponent);
    check(FXComponent);

    MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;

    SetLifeSpan(5.f);

    CollisionComponent->OnComponentHit.AddDynamic(this, &AKBProjectileBase::OnProjectileHit);
}

void AKBProjectileBase::OnProjectileHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    if (!GetWorld()) return;

    UGameplayStatics::ApplyRadialDamage(
        GetWorld(),//
        DamageAmount, //
        GetActorLocation(), //
        DamageRadius, //
        UDamageType::StaticClass(), //
        {}, //
        this, //
        GetOwnersController(), //
        bFullDamage);

    Destroy();

    DrawDebugSphere(GetWorld(), GetActorLocation(), DamageRadius, 16, FColor::Cyan, false, 1.f);

    FXComponent->PlayImpactFX(Hit);
}

AController* AKBProjectileBase::GetOwnersController()
{
    APawn* Pawn = Cast<APawn>(GetOwner());
    
    if (!IsValid(Pawn)) return nullptr;
    return Pawn ? Pawn->GetController() : nullptr;
}

