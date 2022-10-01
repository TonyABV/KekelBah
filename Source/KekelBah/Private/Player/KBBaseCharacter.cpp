// Fill out your copyright notice in the Description page of Project Settings.


#include "KBBaseCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
AKBBaseCharacter::AKBBaseCharacter()
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
    PlayerInputComponent->BindAction("Walk", IE_Pressed, this, &AKBBaseCharacter::Walk);
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
    GetCharacterMovement()->MaxWalkSpeed = 1000.f;
    GetCharacterMovement()->MaxWalkSpeed = 1000.f;
    bIsSprinting = true;
}

void AKBBaseCharacter::CancelSprint() 
{
    if (bIsWalking)
    {
        GetCharacterMovement()->MaxWalkSpeed = 200.f;
    }
    else
    {
        GetCharacterMovement()->MaxWalkSpeed = 600.f;
    }
    bIsSprinting = false;
}

void AKBBaseCharacter::Walk() 
{
    switch (bIsWalking)
    {
        case false: 
            bIsWalking = true;
            GetCharacterMovement()->MaxWalkSpeed = 200.f;
            break;
        case true:
            bIsWalking = false;
            GetCharacterMovement()->MaxWalkSpeed = 600.f;
            break;
    }
}
