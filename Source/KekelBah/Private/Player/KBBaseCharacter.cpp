// Fill out your copyright notice in the Description page of Project Settings.

#include "KBBaseCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/KBBaseCharacterMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/Components/KBHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Controller.h"
#include "KBBaseWeaponActor.h"
#include "KBWeaponComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"


DEFINE_LOG_CATEGORY_STATIC(BaseChar, All, All);

// Sets default values
AKBBaseCharacter::AKBBaseCharacter(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<UKBBaseCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;
    SpringArmComponent->SocketOffset = FVector(0.f, 100.f, 80.f);

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);
    
    HealthComponent = CreateDefaultSubobject<UKBHealthComponent>("HealthComponent");

    TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>("TextRenderComponent");
    TextRenderComponent->SetupAttachment(GetRootComponent());
    TextRenderComponent->SetOwnerNoSee(false);

    WeaponComponent = CreateDefaultSubobject<UKBWeaponComponent>("WeaponComponent");

    CameraCollisionComponent = CreateDefaultSubobject<USphereComponent>("CameraCollisionComponent");
    CameraCollisionComponent->SetupAttachment(CameraComponent);
    CameraCollisionComponent->SetSphereRadius(10.f);
    CameraCollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}

// Called when the game starts or when spawned
void AKBBaseCharacter::BeginPlay()
{
    Super::BeginPlay();

    check(GetMesh());

    HealthComponent->OnDead.AddUObject(this, &AKBBaseCharacter::OnDeath);

    HealthComponent->OnHealthChanged.AddUObject(this, &AKBBaseCharacter::OnHealthChanged);
    OnHealthChanged(HealthComponent->GetCurrentHealth());

    LandedDelegate.AddDynamic(this, &AKBBaseCharacter::OnGroundLanded);

    CameraCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AKBBaseCharacter::OnCameraCollisionBeginOverlap);
    CameraCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &AKBBaseCharacter::OnCameraCollisionEndOverlap);

}

// Called every frame
void AKBBaseCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AKBBaseCharacter::OnGroundLanded(const FHitResult& Hit)
{
    float LandVelocity = -GetVelocity().Z;

    UE_LOG(BaseChar, Display, TEXT("LandVelocity = %f"), LandVelocity);

    if (LandVelocity < LandVelocityRangeForDamage.X) return;

    float Damage = FMath::GetMappedRangeValueClamped(LandVelocityRangeForDamage, LandDamageRange, LandVelocity);

    TakeDamage(Damage, {}, nullptr, nullptr);

    UE_LOG(BaseChar, Display, TEXT("LandDamage = %f"), Damage);
}

// Called to bind functionality to input
void AKBBaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    PlayerInputComponent->BindAxis("MoveForward", this, &AKBBaseCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AKBBaseCharacter::MoveRight);
    PlayerInputComponent->BindAxis("LookUp", this, &AKBBaseCharacter::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("LookAround", this, &AKBBaseCharacter::AddControllerYawInput);

    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AKBBaseCharacter::Jump);
    PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AKBBaseCharacter::BeginSpring);
    PlayerInputComponent->BindAction("Run", IE_Released, this, &AKBBaseCharacter::CancelSprint);
    PlayerInputComponent->BindAction("SlowStep", IE_Pressed, this, &AKBBaseCharacter::SlowStepSwitcher);
    PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &UKBWeaponComponent::StartFire);
    PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &UKBWeaponComponent::EndFire);
    PlayerInputComponent->BindAction("NextWeapon", IE_Pressed, WeaponComponent, &UKBWeaponComponent::NextWeapon);
    PlayerInputComponent->BindAction("Reload", IE_Pressed, WeaponComponent, &UKBWeaponComponent::Reload);
}

void AKBBaseCharacter::MoveForward(float Scale)
{
    AddMovementInput(GetActorForwardVector(), Scale);
}

void AKBBaseCharacter::MoveRight(float Scale)
{
    AddMovementInput(GetActorRightVector(), Scale);
}

void AKBBaseCharacter::BeginSpring()
{
    bWantSprinting = true;
}

void AKBBaseCharacter::CancelSprint()
{
    bWantSprinting = false;
}

void AKBBaseCharacter::SlowStepSwitcher()
{
    if (bWantSlowStepping)
    {
        bWantSlowStepping = false;
    }
    else
    {
        bWantSlowStepping = true;
    }
    bWantSprinting = false;
}

void AKBBaseCharacter::OnDeath()
{
    //PlayAnimMontage(DeathAnim);
    GetCharacterMovement()->DisableMovement();
    SetLifeSpan(5.f);

    if (IsValid(Controller))
    {
        Controller->ChangeState(NAME_Spectating);
    }

    GetCapsuleComponent()->SetCollisionResponseToChannels(ECollisionResponse::ECR_Ignore);

    WeaponComponent->EndFire();

    GetMesh()->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
    GetMesh()->SetSimulatePhysics(true);

    UGameplayStatics::PlaySoundAtLocation(GetWorld(), DeathSound, GetActorLocation());
}

void AKBBaseCharacter::OnHealthChanged(float NewHealth)
{
    TextRenderComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), NewHealth)));
}

void AKBBaseCharacter::OnCameraCollisionBeginOverlap(UPrimitiveComponent* PrimitiveComponent, AActor* Actor,
    UPrimitiveComponent* PrimitiveComponent1, int I, bool bArg, const FHitResult& HitResult)
{
    CheckOverlap();
}

void AKBBaseCharacter::OnCameraCollisionEndOverlap(UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    CheckOverlap();
}

void AKBBaseCharacter::CheckOverlap()
{
    const bool HideMesh = CameraCollisionComponent->IsOverlappingComponent(GetCapsuleComponent());
    GetMesh()->SetOwnerNoSee(HideMesh);

    TArray<USceneComponent*> ChildrenComponents;
    GetMesh()->GetChildrenComponents(true, ChildrenComponents);

    for (auto Child : ChildrenComponents)
    {
        const auto ChildPrimComp = Cast<UPrimitiveComponent>(Child);
        if (ChildPrimComp)
        {
            ChildPrimComp->SetOwnerNoSee(HideMesh);
        }
    }
}

bool AKBBaseCharacter::IsSlowStepping()
{
    if (IsSprinting()) return false;

    return bWantSlowStepping && !GetVelocity().IsZero();
}

bool AKBBaseCharacter::IsSprinting()
{
    return bWantSprinting && !GetVelocity().IsZero();
}

float AKBBaseCharacter::GetMovementDirection()
{
    FVector ForwardVector = GetActorForwardVector();
    FVector VelocityDirection = GetVelocity().GetSafeNormal();

    float AngleBetweene =  FMath::RadiansToDegrees(FMath::Acos(FVector::DotProduct(ForwardVector, VelocityDirection)));
    float Sign = FMath::Sign(FVector::CrossProduct(ForwardVector, VelocityDirection).Z);

    return AngleBetweene * Sign;
}

void AKBBaseCharacter::SetPlayerColor(const FLinearColor& LinearColor)
{
    const auto MaterialInstance = GetMesh()->CreateAndSetMaterialInstanceDynamic(0);
    if (!MaterialInstance) return;

    MaterialInstance->SetVectorParameterValue(MaterialColorName, LinearColor);
}
