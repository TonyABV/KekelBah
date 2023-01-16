// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "KBBaseAnimNotify.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnNotified, USkeletalMeshComponent*)

UCLASS()
class KEKELBAH_API UKBBaseAnimNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
    virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

    FOnNotified OnNotified;
};
