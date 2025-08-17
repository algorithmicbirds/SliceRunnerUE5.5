// Fill out your copyright notice in the Description page of Project Settings.

#include "Abilities/Combat/SRAbility_LookAt.h"
#include "PlayerCharacter/SRBaseCharacter.h"
#include "AnimInstance/SRBaseAnimInstance.h"
#include "AnimInstance/Enemy/SREnemyAnimInstance.h"

void USRAbility_LookAt::ActivateAbility(const FSRAbilityActivationContext &Context)
{
    if (USREnemyAnimInstance *EnemyAnimInstance = Cast<USREnemyAnimInstance>(GetSRAnimInstance()))
    {
        
    }
}

void USRAbility_LookAt::EndAbility() {}
