// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter/SREnemy_GunType.h"
#include "AbilitySystem/SRAbilityManagerComponent.h"
#include "GameplayTags/SRGameplayTags.h"
#include "Debug/DebugHelper.h"
#include "AbilitySystem/SRAbilitySet.h"
#include "Controllers/SRAIController.h"

ASREnemy_GunType::ASREnemy_GunType() {}

void ASREnemy_GunType::RecieveHitEvent()
{
     if (SRAMC)
     {
         SRAMC->StartAbilityByTag(SRGameplayTags::AbilityTag_Death);
     }
}

void ASREnemy_GunType::PossessedBy(AController *NewController)
{
    Super::PossessedBy(NewController);
    checkf(AbilitySet, TEXT("Forgot to assign Ability Set To Enemy Gun Type"));
    if (SRAMC)
    {
        AbilitySet->GiveAbilityToManager(SRAMC);
    }
    if (ASRAIController* AIController = Cast<ASRAIController>(NewController))
    {
        
    }
}