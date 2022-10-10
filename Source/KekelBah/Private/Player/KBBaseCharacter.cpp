// Fill out your copyright notice in the Description page of Project Settings.


#include "KBBaseCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/KBBaseCharacterMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AKBBaseCharacter::AKBBaseCharacter(const FObjectInitializer& ObjectInitializer) :
Super(ObjectInitializer.SetDefaultSubobjectClass<UKBBaseCharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);
}

// Called when the game starts or when spawned
void AKBBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

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
    //GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
    bWantSprinting = true;
}

void AKBBaseCharacter::CancelSprint() 
{
    //if (bWantSlowStepping)
    /*{
        GetCharacterMovement()->MaxWalkSpeed = SlowSteppingSpeed;
    }
    else
    {
        GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed;
    }*/
    bWantSprinting = false;
}

void AKBBaseCharacter::SlowStepSwitcher() 
{
    switch (bWantSlowStepping)
    {
        case false: 
            bWantSlowStepping = true;
            //GetCharacterMovement()->MaxWalkSpeed = SlowSteppingSpeed;
            break;
        case true:
            bWantSlowStepping = false;
            //GetCharacterMovement()->MaxWalkSpeed = DefaultWalkSpeed;
            break;
    }
    bWantSprinting = false;
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
