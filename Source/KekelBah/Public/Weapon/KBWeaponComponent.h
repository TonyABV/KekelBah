// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Weapon/KBBaseWeaponActor.h"
#include "KBWeaponComponent.generated.h"

class AKBBaseWeaponActor;

USTRUCT(BlueprintType)
struct FWeaponData
{
    GENERATED_BODY()

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    TSubclassOf<AKBBaseWeaponActor> WeaponClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    UAnimMontage* ReloadAnim;
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class KEKELBAH_API UKBWeaponComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UKBWeaponComponent();

    virtual void StartFire();

    void EndFire();

    virtual void NextWeapon();
    
    void Reload();

    bool GetUIWeaponData(FUIWeaponData& UIWeaponData) const;

    bool GetCurrentAmmoData(FWeaponAmmo& WeaponAmmo) const;

    bool TryAddAmmo(TSubclassOf<AKBBaseWeaponActor> WeaponType, int32 ClipAmount);

    AKBBaseWeaponActor* GetWeapon(TSubclassOf<AKBBaseWeaponActor> WeaponClass);

protected:

	virtual void BeginPlay() override;

    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    void SpawnWeapons();

    void AttachWeaponToMesh(AKBBaseWeaponActor* Weapon, USkeletalMeshComponent* SkeletalMesh, const FName& SocketName);

    void EquipWeapon(int32 WeaponIndex);

    void PlayAnimMontage(UAnimMontage* AnimMontage);

    void InitAnimations();

    UFUNCTION()
    void OnEquipFinished(USkeletalMeshComponent* MeshComp);

    UFUNCTION()
    void OnReloadFinished(USkeletalMeshComponent* MeshComp);

    bool CanFire() const;

    bool CanEquip() const;

    bool CanReload() const;

    void OnEmptyClip(AKBBaseWeaponActor* EmptyWeapon);

    void ChangeClip();

protected:

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TArray<FWeaponData> WeaponData;

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponEquipPointName = "WeaponPoint";

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponArmoryPointName = "ArmorySocket";

    UPROPERTY()
    AKBBaseWeaponActor* CurrentWeapon = nullptr;

    UPROPERTY()
    UAnimMontage* CurrentReloadAnim = nullptr;

    UPROPERTY()
    TArray<AKBBaseWeaponActor*> Weapons;

    int32 CurrentWeaponIndex = 0.f;

    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    UAnimMontage* ChangeWeaponAnimation;

    bool bEquipInProgress = false;

    bool bReloadInProgress = false;

    template<typename T>
    T* FindAnimNotifyByClass(UAnimSequenceBase* Animation) const
    {
        for(const auto NotifyEvent : Animation->Notifies)
        {
            T* Notify = Cast<T>(NotifyEvent.Notify);
            if (IsValid(Notify)) return Notify;
        }
        return nullptr;
    }
};
