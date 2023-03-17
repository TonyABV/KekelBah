// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "KBPlayerState.h"
#include "GameFramework/Character.h"
#include "KBBaseCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UKBHealthComponent;
class UTextRenderComponent;
class AKBBaseWeaponActor;
class UKBWeaponComponent;

UCLASS()
class KEKELBAH_API AKBBaseCharacter : public ACharacter
{
    GENERATED_BODY()

public:

    AKBBaseCharacter(const FObjectInitializer& ObjectInitializer);
    
    virtual void Tick(float DeltaTime) override;

protected:
    virtual void BeginPlay() override;
    
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "CameraComponent")
    UCameraComponent* CameraComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpringArmComponent")
    USpringArmComponent* SpringArmComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HealthComponent")
    UKBHealthComponent* HealthComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TextComponent")
    UTextRenderComponent* TextRenderComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Component")
    UKBWeaponComponent* WeaponComponent;

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

    UPROPERTY(EditDefaultsOnly, Category = "Material")
    FName MaterialColorName = "Paint Color";

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

    virtual void OnDeath();
    
    void OnHealthChanged(float NewHealth);
    
public:
    UFUNCTION(BlueprintCallable, Category = "Movement")
    bool IsSlowStepping();

    UFUNCTION(BlueprintCallable, Category = "Movement")
    bool IsSprinting();

    UFUNCTION(BlueprintCallable, Category = "Movement")
    float GetMovementDirection();

    void SetPlayerColor(const FLinearColor& LinearColor);
};
