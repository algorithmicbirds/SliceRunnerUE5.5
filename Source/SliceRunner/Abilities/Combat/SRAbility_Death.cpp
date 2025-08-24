// Fill out your copyright notice in the Description page of Project Settings.

#include "Abilities/Combat/SRAbility_Death.h"
#include "Debug/DebugHelper.h"
#include "PlayerCharacter/SRBaseCharacter.h"
#include "AbilitySystem/SRMontageManager.h"
#include "GameFramework/CharacterMovementComponent.h"

void USRAbility_Death::ActivateAbility(const FSRAbilityActivationContext &Context)
{
    if (ASRBaseCharacter *Character = GetSRCharacter())
    {
        if (AController* Controller = Cast<AController>(Character->GetController()))
        {
            Controller->DisableInput(nullptr);
            //MontageManger->TryAndPlayMontage(this, DeathMontage, GetSRAnimInstance(), true);
            Character->GetCharacterMovement()->DisableMovement();
        }
    }
}
