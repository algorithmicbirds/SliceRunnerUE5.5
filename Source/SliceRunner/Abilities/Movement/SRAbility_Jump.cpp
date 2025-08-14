// Fill out your copyright notice in the Description page of Project Settings.

#include "Abilities/Movement/SRAbility_Jump.h"
#include "PlayerCharacter/SRBaseCharacter.h"
#include "PlayerCharacter/SRWallRunComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Debug/DebugHelper.h"

void USRAbility_Jump::ActivateAbility(const FSRAbilityActivationContext &Context)
{
    if (ASRBaseCharacter *Character = GetSRCharacter())
    {
        if (USRWallRunComponent *WallRunComp = Character->FindComponentByClass<USRWallRunComponent>())
        {
            if (WallRunComp->IsWallRunning())
            {
                WallRunComp->StopWallRun();
                FVector PlaneContraintNormal = Character->GetCharacterMovement()->GetPlaneConstraintNormal();
                const float DashStrength = Character->GetVelocity().Length();
                FVector UpwardForce = FVector(0, 0, DashStrength);
                Character->LaunchCharacter(PlaneContraintNormal * DashStrength + UpwardForce, false, true);
            }
        }
        Character->Jump();
    }
}

void USRAbility_Jump::EndAbility()
{
    if (ASRBaseCharacter *Character = GetSRCharacter())
    {
        Character->StopJumping();
    }
}
