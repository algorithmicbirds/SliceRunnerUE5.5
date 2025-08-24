// Fill out your copyright notice in the Description page of Project Settings.

#include "Abilities/Combat/SRAbility_Death.h"
#include "Debug/DebugHelper.h"
#include "PlayerCharacter/SRBaseCharacter.h"

void USRAbility_Death::ActivateAbility(const FSRAbilityActivationContext &Context)
{
    if (ASRBaseCharacter *Character = GetSRCharacter())
    {
        Character->Destroy();
    }
}
