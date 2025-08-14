// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UObject/Object.h"
#include "GameplayTagContainer.h"
#include "SRAbilityBase.generated.h"

class ASRBaseCharacter;
class USRBaseAnimInstance;
struct FSRCurrentActorInfo;
struct FSRAbilityActivationContext;
class USRMontageManager;
class USRAbilityManagerComponent;
/**
 *
 */
UCLASS(Blueprintable)
class SLICERUNNER_API USRAbilityBase : public UObject
{
    GENERATED_BODY()
public:
    virtual void ActivateAbility(const FSRAbilityActivationContext &Context);
    virtual void EndAbility();

    void SetActorInfo(const FSRCurrentActorInfo *InActorInfo) { CurrentActorInfo = InActorInfo; }
    ASRBaseCharacter *GetSRCharacter() const;
    UWorld *GetWorld() const;
    USRBaseAnimInstance *GetSRAnimInstance() const;
    void SetCurrentAnimMontage(UAnimMontage *InMontage);
    UAnimMontage *GetCurrentAnimMontage() const;
    void SetAbilityTag(FGameplayTag InAbilityTag) { AbilityTag = InAbilityTag; }
    void RequestEndAbility();

    UPROPERTY()
    TObjectPtr<USRMontageManager> MontageManger;

    UPROPERTY()
    TObjectPtr<USRAbilityManagerComponent> AbilityManager;

protected:
    mutable const FSRCurrentActorInfo *CurrentActorInfo = nullptr;

    UPROPERTY()
    TObjectPtr<UAnimMontage> CurrentAnimMontage = nullptr;

    FGameplayTag AbilityTag;
};
