// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AbilitySystem/SRAbilityBase.h"
#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "SRAbility_Attack.generated.h"

class UAnimMontage;
class USRWeaponBase;

    /**
 *
 */
UCLASS()
class SLICERUNNER_API USRAbility_Attack : public USRAbilityBase
{
    GENERATED_BODY()
public:

    virtual void ActivateAbility(const FSRAbilityActivationContext &Context) override;
    virtual void EndAbility() override;


protected:
    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    TArray<TObjectPtr<UAnimMontage>> AttackAnimComboMantages;

    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    bool bIsAllowedToInterrupt = true;

    UPROPERTY(EditDefaultsOnly, Category = "HitDetection")
    FName HitDetectionStartSocket = "blade_base_socket";

    UPROPERTY(EditDefaultsOnly, Category = "HitDetecion")
    FName HitDetectionEndSocket = "blade_tip_socket";


private:
    void UpdateAttackIndex();
    void OnMontageCompleted();
    void OnMontageInterrupted();
    void AttackWindowOpened(const FGameplayTag &Tag);
    void AttackState(const FGameplayTag &Tag);
    void PlayAttackMontage();

    int AttackCount = 0;
    UPROPERTY()
    TObjectPtr<USRBaseAnimInstance> AnimInstance = nullptr;

    UPROPERTY()
    TObjectPtr<ASRBaseCharacter> Character = nullptr;

    UPROPERTY()
    TObjectPtr<USRWeaponBase> WeaponMesh = nullptr;
    
};
