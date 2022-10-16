// Fill out your copyright notice in the Description page of Project Settings.

#include "KBBaseCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/KBBaseCharacterMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Player/Components/KBHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/Controller.h"

// Sets default values
AKBBaseCharacter::AKBBaseCharacter(const FObjectInitializer& ObjectInitializer)
    : Super(ObjectInitializer.SetDefaultSubobjectClass<UKBBaseCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);

    HealthComponent = CreateDefaultSubobject<UKBHealthComponent>("HealthComponent");

    TextRenderComponent = CreateDefaultSubobject<UTextRenderComponent>("TextRenderComponent");
    TextRenderComponent->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void AKBBaseCharacter::BeginPlay()
{
    Super::BeginPlay();

    HealthComponent->OnDead.AddUObject(this, &AKBBaseCharacter::OnDeath);

    HealthComponent->OnHealthChanged.AddUObject(this, &AKBBaseCharacter::OnHealthChanged);
    OnHealthChanged(HealthComponent->GetCurrentHealth());
}

// Called every frame
void AKBBaseCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
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
    PlayAnimMontage(DeathAnim);
    GetCharacterMovement()->DisableMovement();
    SetLifeSpan(5.f);

    if (IsValid(Controller))
    {
        Controller->ChangeState(NAME_Spectating);
    }

    UE_LOG(LogTemp, Log, TEXT("%s death"), *GetName());
}

void AKBBaseCharacter::OnHealthChanged(float NewHealth)
{
    TextRenderComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), NewHealth)));
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
