// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "KBBaseCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

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

protected:	
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void MoveForward(float Scale);
	void MoveRight(float Scale);

    void BeginSpring();
    void CancelSprint();
    void SlowStepSwitcher();

public:

    UFUNCTION(BlueprintCallable)
    bool IsSlowStepping();

    UFUNCTION(BlueprintCallable)
    bool IsSprinting();

};
