// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/SRAbilitySet.h"
#include "AbilitySystem/SRAbilityManagerComponent.h"
#include "AbilitySystem/SRAbilityBase.h"

void USRAbilitySet::GiveAbilityToManager(USRAbilityManagerComponent *AMC)
{
    for (int32 AbilityIndex = 0; AbilityIndex < GrantedGameplayAbilities.Num(); ++AbilityIndex)
    {
        const FSRGameplayAbility &AbilityToGrant = GrantedGameplayAbilities[AbilityIndex];
        USRAbilityBase *AbilityInstance = NewObject<USRAbilityBase>(AMC, AbilityToGrant.Ability);
        AMC->GiveAbility(AbilityToGrant.AbilityTag, AbilityInstance);
    }
}
