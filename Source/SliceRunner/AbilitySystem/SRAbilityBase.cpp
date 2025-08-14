// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/SRAbilityBase.h"
#include "PlayerCharacter/SRBaseCharacter.h"
#include "AnimInstance/SRBaseAnimInstance.h"
#include "GameplayTasksComponent.h"
#include "AbilitySystem/SRAbilityData.h"
#include "AbilitySystem/SRMontageManager.h"
#include "AbilitySystem/SRAbilityManagerComponent.h"
#include "Debug/DebugHelper.h"

void USRAbilityBase::ActivateAbility(const FSRAbilityActivationContext &Context)
{
}

void USRAbilityBase::EndAbility() { }

ASRBaseCharacter *USRAbilityBase::GetSRCharacter() const
{
    return CurrentActorInfo ? Cast<ASRBaseCharacter>(CurrentActorInfo->OwnerActor.Get()) : nullptr;
}

UWorld *USRAbilityBase::GetWorld() const
{
    return CurrentActorInfo ? CurrentActorInfo->OwnerActor->GetWorld() : nullptr;
}

USRBaseAnimInstance *USRAbilityBase::GetSRAnimInstance() const
{
    return CurrentActorInfo ? Cast<USRBaseAnimInstance>(CurrentActorInfo->AnimInstance) : nullptr;
}

void USRAbilityBase::SetCurrentAnimMontage(UAnimMontage *InMontage) { CurrentAnimMontage = InMontage; }

UAnimMontage *USRAbilityBase::GetCurrentAnimMontage() const { return CurrentAnimMontage; }

void USRAbilityBase::RequestEndAbility()
{
    if (AbilityManager)
    {
        if (!AbilityManager->HasAbilityActiveTag(AbilityTag))
        {
            return;
        }
        AbilityManager->StopAbilityByTag(AbilityTag);
    }
    else
    {
        Debug::Print("Ability manager is null");
    }
}
