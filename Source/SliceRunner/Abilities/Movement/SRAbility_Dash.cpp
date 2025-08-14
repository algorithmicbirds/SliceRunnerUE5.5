// Fill out your copyright notice in the Description page of Project Settings.

#include "Abilities/Movement/SRAbility_Dash.h"
#include "PlayerCharacter/SRBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Debug/DebugHelper.h"

USRAbility_Dash::USRAbility_Dash() {}

void USRAbility_Dash::ActivateAbility(const FSRAbilityActivationContext &Context)
{
    Super::ActivateAbility(Context);
    if (ASRBaseCharacter *Character = GetSRCharacter())
    {
        if (Character->GetCharacterMovement()->IsFalling())
        {
            UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.2f);
        }
        else
        {
            Debug::Print("Request end of ability Dash");
            RequestEndAbility();
        }
    }
}

void USRAbility_Dash::EndAbility()
{
    Super::EndAbility();
    if (ASRBaseCharacter *Character = GetSRCharacter())
    {
        UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 1.0f);
        const FVector DashDir = Character->Controller->GetControlRotation().Vector();
        const float DashStrength = 1000.0f;
        Character->LaunchCharacter(DashDir * DashStrength, true, true);
    }
}
