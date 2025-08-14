// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter/SRBaseCharacter.h"
#include "AbilitySystem/SRAbilityManagerComponent.h"
#include "Debug/DebugHelper.h"
#include "PlayerCharacter/SRWeaponBase.h"

ASRBaseCharacter::ASRBaseCharacter()
{
    PrimaryActorTick.bCanEverTick = false;
    PrimaryActorTick.bStartWithTickEnabled = false;

    SRAMC = CreateDefaultSubobject<USRAbilityManagerComponent>(TEXT("AbilityManagerComponent"));
    WeaponMesh = CreateDefaultSubobject<USRWeaponBase>(TEXT("WeaponMesh"));
}

USRAbilityManagerComponent *ASRBaseCharacter::GetAbilityManagerComponent() const { return SRAMC; }


void ASRBaseCharacter::PossessedBy(AController *NewController)
{
    Super::PossessedBy(NewController);
    if (SRAMC)
    {
        SRAMC->InitActorInfo(this);
    }
}
