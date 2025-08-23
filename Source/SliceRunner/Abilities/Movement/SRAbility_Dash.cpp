// Fill out your copyright notice in the Description page of Project Settings.

#include "Abilities/Movement/SRAbility_Dash.h"
#include "PlayerCharacter/SRBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"

USRAbility_Dash::USRAbility_Dash() {}

void USRAbility_Dash::ActivateAbility(const FSRAbilityActivationContext &Context)
{
    Super::ActivateAbility(Context);
    if (ASRBaseCharacter *Character = GetSRCharacter())
    {
        if (Character->GetCharacterMovement()->IsFalling())
        {
            OriginalAirControl = Character->GetCharacterMovement()->AirControl;
            Character->GetCharacterMovement()->AirControl = 1.0f;
            UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.2f);
        }
        else
        {
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
        Character->GetCharacterMovement()->AirControl = OriginalAirControl;
        Character->LaunchCharacter(DashDir * DashStrength, true, true);
    }
}
