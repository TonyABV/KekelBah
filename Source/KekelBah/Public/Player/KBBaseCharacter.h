// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "KBBaseCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UKBHealthComponent;
class UTextRenderComponent;

UCLASS()
class KEKELBAH_API AKBBaseCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    // Sets default values for this character's properties
    AKBBaseCharacter(const FObjectInitializer& ObjectInitializer);

    // Called every frame
    virtual void Tick(float DeltaTime) override;

protected:
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraComponent")
    UCameraComponent* CameraComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpringArmComponent")
    USpringArmComponent* SpringArmComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HealthComponent")
    UKBHealthComponent* HealthComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TextComponent")
    UTextRenderComponent* TextRenderComponent;

    UPROPERTY()
    bool bWantSprinting = false;

    UPROPERTY()
    bool bWantSlowStepping = false;

    UPROPERTY(EditDefaultsOnly)
    float SlowSteppingSpeed = 200.f;

    UPROPERTY(EditDefaultsOnly)
    float SprintSpeed = 1000.f;

    UPROPERTY(EditDefaultsOnly)
    float DefaultWalkSpeed = 600.f;

    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    UAnimMontage* DeathAnim;

    UPROPERTY(EditDefaultsOnly, Category = "Damage")
    FVector2D LandDamageRange = FVector2D{20.f, 100.f};

    UPROPERTY(EditDefaultsOnly, Category = "Damage")
    FVector2D LandVelocityRangeForDamage = FVector2D{500.f, 1000.f};

protected:

    UFUNCTION()
    void OnGroundLanded(const FHitResult& Hit);

    // Called to bind functionality to input
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

    void MoveForward(float Scale);
    void MoveRight(float Scale);

    void BeginSpring();
    void CancelSprint();
    void SlowStepSwitcher();

    void OnDeath();
    
    void OnHealthChanged(float NewHealth);

public:
    UFUNCTION(BlueprintCallable, Category = "Movement")
    bool IsSlowStepping();

    UFUNCTION(BlueprintCallable, Category = "Movement")
    bool IsSprinting();

    UFUNCTION(BlueprintCallable, Category = "Movement")
    float GetMovementDirection();
    
};
